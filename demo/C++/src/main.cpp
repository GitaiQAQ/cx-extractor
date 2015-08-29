#include <sstream>
#include <string>
#include <fstream>
#include <iterator>
#include <curl/curl.h>
#include <boost/regex.hpp>
#include <iostream>
#include <ctype.h>
 
boost::regex _doctype;
boost::regex _comment;
boost::regex _javascript;
boost::regex _css;
boost::regex _special_char;
boost::regex _other_tag;
boost::regex _empty_char;

bool raw;

std::vector<std::string> lines;
std::vector<std::string> lines_raw;
std::vector<int> blocks;

std::string parse (std::string str, int threshold);
void assign_regex();
void removeSpace (std::string & str);
void removeTags  (std::string & HTML);
void getAllLine (std::string & HTML);
void statistic_line (std::string & HTML);
void statistic_block (int blockWidth);
int findSurge (int start, int threshold);
int findDive (int surgePoint);
void getContent (int start, int end, std::string & content);

namespace
{
    std::size_t callback(
            const char* in,
            std::size_t size,
            std::size_t num,
            std::string* out)
    {
        const std::size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    }
};

int main(int argc, char *argv[])
{
    if (argc>2)
    {
      raw = true;
    }
    CURL *curl = curl_easy_init();
    if (curl!=NULL)
    {
      curl_easy_setopt(curl, CURLOPT_URL,argv[1]);
      curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10);
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

      // Response information.
      int httpCode(0);
      std::unique_ptr<std::string> httpData(new std::string());
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &callback);

      curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

      // Capture the HTTP response code, and clean up.
      curl_easy_perform(curl);
      curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
      if (httpCode == 200)
      {
          assign_regex();
          parse(*httpData.get(),172);
      }
      else
      {
          printf("Couldn't GET:%d\n",httpCode);
          return 1;
      }
      return 0;
    }
    return 1;
}

std::string parse (std::string str, int threshold){
  statistic_line (str);
  lines_raw = lines;
  removeTags(str);
  statistic_line (str);
  statistic_block (3);

  std::string content;
  int start = 0 ,end = 0;
  while (1)
  {
    start = findSurge (end, threshold);
    if (start < 0)
    {
      //std::cout << "no more content has been found\n";
      break;
    }
    end = findDive(start);
    getContent(start, end, content);
  }
  /*std::ofstream outFile("./ofstream.data");
  outFile << content;
  outFile.close();*/
  std::cout << content;
  return content;
}

/**
 * 初始化正则表达式变量
 *
 * 仅在系统初始化时编译一次所有的正则表达式
 */
void assign_regex()
{
  _doctype    = boost::regex ("(?is)<!DOCTYPE.*?>", boost::regex::icase|boost::regex::perl);
  _comment    = boost::regex ("(?is)<!--.*?-->", boost::regex::icase|boost::regex::perl);
  _javascript   = boost::regex ("(?is)<script.*?>.*?</script>", boost::regex::icase|boost::regex::perl);
  _css      = boost::regex ("(?is)<style.*?>.*?</style>", boost::regex::icase|boost::regex::perl);
  _special_char = boost::regex ("&.{2,5};|&#.{2,5};", boost::regex::icase|boost::regex::perl);
  _other_tag    = boost::regex ("(?is)<.*?>", boost::regex::icase|boost::regex::perl);
  _empty_char   = boost::regex ("\\s", boost::regex::icase|boost::regex::perl);
  
}

void removeSpace  (std::string & str)
{
  std::basic_string<char>::iterator iter = str.begin();
  while (iter != str.end())
  {
    //空格，制表符，换行符，回车符，换页符，报警符和转义符
    if (/*(' ' == (*iter)) || */('\t' == (*iter)) || ('\n' == (*iter)) || ('\r' == (*iter)) || ('\f' == (*iter)) || ('\a' == (*iter)) || ('\e' == (*iter)))
    {
      iter = str.erase(iter);
    }
    else
      iter++;
  }
}

void removeTags  (std::string & HTML)
{
  HTML = boost::regex_replace(HTML, _doctype, "");
  HTML = boost::regex_replace(HTML, _comment, "");
  HTML = boost::regex_replace(HTML, _javascript, "");
  HTML = boost::regex_replace(HTML, _css, "");
  HTML = boost::regex_replace(HTML, _special_char, "");
  HTML = boost::regex_replace(HTML, _other_tag, "");
}

int getOneLine (std::string & HTML, std::basic_string<char>::iterator & iter, std::string & line)
{
  line.clear();
  while( iter != HTML.end() && '\n' != (*iter))
  {
    line.push_back(*iter);
    iter++;
  }
  
  removeSpace (line);

  if (iter == HTML.end()) 
    return 0; 
  else if ('\n' == (*iter))
  {
    iter++;
    return 1;
  }   
  else 
    return -1;
}

void getAllLine (std::string & HTML)
{
  lines.clear();

  std::string line;
  std::basic_string<char>::iterator iter;
  iter = HTML.begin();

  while (getOneLine(HTML, iter, line) > 0)
  {
    lines.push_back(line);
  }
}

void statistic_line (std::string & HTML)
{
  getAllLine (HTML);

  /*std::vector<std::string>::iterator it;
  it = lines.begin();
  while(it != lines.end())
  {
    std::cout << it->size() << '\n';
    it++;
  }*/
}

void statistic_block (int blockWidth)
{
  blocks.clear();

  for(int i=0; i < lines.size() - blockWidth; i++)
  {
    int block_len = 0;
    for (int j=0; j < blockWidth; j++)
      block_len += lines[i+j].length();
    blocks.push_back(block_len);
  }

  for(int i=0; i < blocks.size(); i++)
  {
    //std::cout << blocks[i] << '\n';
  }
}

int findSurge (int start, int threshold)
{
  for(int i = start; i < blocks.size(); i++)
  {
    if ( blocks[i] > threshold 
      && blocks[i+1] > 0      //紧随骤升点的行块长度不能为0
      && blocks[i+2] > 0
      && blocks[i+3] > 0 )
      return i;
  }
  return -1;
}

int findDive (int surgePoint)
{
  for (int i = surgePoint + 1; i < blocks.size(); i++)
  {
    if (blocks[i] == 0 && blocks[i+1] == 0)
      return i;
  }
  return blocks.size() -1;
}

void getContent (int start, int end, std::string & content)
{
  int presize;
  if (raw)
  {
    for(int i = start; i<= end; i ++)
      {
        if (lines[i].size()!=0||presize!=0)
        {
          content += lines_raw[i];
          content.push_back('\n');
        }
        presize = lines[i].size();
      }
  }else{
    for(int i = start; i<= end; i ++)
    {
      if (lines[i].size()!=0||presize!=0)
      {
        content += lines[i];
        content.push_back('\n');
      }
      presize = lines[i].size();
    }
  }
}


