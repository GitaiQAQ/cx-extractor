## Boost

### [Download](http://www.boost.org/users/history/version_1_59_0.html)

### Unzip

> tar -zxvf boost_1_54_0.tar.gz

### Test

#### example.cpp

```
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>
 
int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;
    std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
    std::cout << std::endl;
}

```

> g++ -I ~/boost/boost_1_54_0/ ./example.cpp -o example 

> echo 1 2 3 | ./example

> OUTPUT: 3 6 9


### Make

> sudo ./bootstrap.sh
> sudo ./b2 install

### Test
#### example2.cpp

```
#include <boost/regex.hpp>
#include <string>
#include <iostream>
 
int main()
{
  std::string line = "Subject: Will Success?";
  boost::regex pat("^Subject: (Re |Aw: )*(.*)");
  while(std::cin)
  {
    std::getline(std::cin, line);
    boost::smatch matches;
    if(boost::regex_match(line, matches, pat))
    {
        std::cout << matches[2] << std::endl;  
    }
  }
}
```

> g++ -I/usr/local/include/ example2.cpp -o example2 /usr/local/lib/libboost_regex.a

> ./example2 < test.txt

> OUTPUT: Will Success?

## Build Html2Act

> make

##Use

> ./html2act http://www.cnblogs.com/jasondan/p/4145305.html

```
事因
最近因为工作特别忙，没怎么光顾博客园，今天睡觉前，想想看看博客园吧，随便点了点阅读排行的东西，发现有篇《GitHub上整理的一些工具》感觉比较有意思就进去看了看，发现内容怎么越看越熟悉啊，再一看不对劲啊，这不是我的文章么，通篇看完后，发现除了标题改了，内容跟我的完全一样，这是赤裸裸的抄袭啊！！！！！！
瞬间有种被强奸的感觉，睡不着觉了，一定得写篇文章谴责一下这种行为！
以下是这篇抄袭我文章的截图：

都上了48小时阅读排行了，话说，要是不上，我还真没有注意到呢！
证据
这是我的文章：✈工欲善其事，必先利其器✔™
看下面的截图，大家注意下我的发布时间是：2014-01-02

我想说的是这是我辛辛苦苦花了将近一年的时间积累下来的！！
就这么被抄袭了，感觉很不是滋味，您这么轻松发表了一篇文章，引来大量关注，您不知道别人劳动的不易么？
=============================================
抄袭我的那篇文章：GitHub上整理的一些工具
注意下他的这篇文章是昨天刚刚发布不久的哦：

哟，这推荐数量还不少呢，我在想抄袭我文章的那位作者，您不心虚么？？？？
我想说的是，您没有注意到我的文章结尾处有这么一出显著的标记么：

目的
写这篇的文章的目的很简单，就是维护个人的知识成果，也让博客园能更好的给大家营造一个积极向上的写作氛围。
在园子里待的时间也不短了，相信每个人热爱积累和分享的园友，都不希望别人直接把自己的东西拿走当成自己的原创发布到博客园首页上。
哪怕是你转载的时候能随便做到以下几点也行啊：

标注这是转载（没有署名也行啊）
对文章内容进行提炼，加入自己的思想
直接转走没关系，至少也尊重下原作者的转载要求吧

前阵子有园友反映说自己发表在博客园上的文章被其他网站给抓走了，dudu回复说这种情况博客园也很难去处理，现在没想到自己的文章居然在博客园内被抄袭了，很不爽。
博客园的发文说明也有要求的，那就是只能发布原创的：

写给抄袭我文章的园友的
写到这心情也平静了许些，不再像刚才那么气愤了。
希望那位抄袭我文章的园友，看到我的这篇文章后能有所理解，以后不要这么随意的抄袭他人的东西作为自己的原创，这样会打击他人积极性的。
我会联系博客园工作人员将您的文章进行移除的。
以希望您不要太在意此事，以后注意点就好，鼓励分享！

```

>  ./html2act http://www.cnblogs.com/jasondan/p/4145305.html raw


```
<div class="postBody">
<div id="cnblogs_post_body" class="cnblogs-markdown"><h2>事因</h2>
<p>最近因为工作特别忙，没怎么光顾博客园，今天睡觉前，想想看看博客园吧，随便点了点阅读排行的东西，发现有篇《GitHub上整理的一些工具》感觉比较有意思就进去看了看，发现内容怎么越看越熟悉啊，再一看不对劲啊，这不是我的文章么，通篇看完后，发现除了标题改了，内容跟我的完全一样，这是赤裸裸的抄袭啊！！！！！！</p>
<p>瞬间有种<strong>被强奸</strong>的感觉，睡不着觉了，一定得写篇文章谴责一下这种行为！</p>
<p>以下是这篇抄袭我文章的截图：</p>
<p><img src="http://images.cnitblog.com/blog/312243/201412/042326027179585.png" /></p>
<p>都上了48小时阅读排行了，话说，要是不上，我还真没有注意到呢！</p>
<h2>证据</h2>
<p><strong>这是我的文章：</strong><a href="http://www.cnblogs.com/jasondan/p/it-memo.html">✈工欲善其事，必先利其器✔™</a></p>
<p>看下面的截图，大家注意下我的发布时间是：<strong>2014-01-02</strong></p>
<p><img src="http://images.cnitblog.com/blog/312243/201412/042330566556453.png" /></p>
<p>我想说的是<strong>这是我辛辛苦苦花了将近一年的时间积累下来的！！</strong></p>
<p>就这么被抄袭了，感觉很不是滋味，您这么轻松发表了一篇文章，引来大量关注，您不知道别人劳动的不易么？</p>
<p>=============================================</p>
<p><strong>抄袭我的那篇文章：</strong><a href="http://www.cnblogs.com/mygxl/p/4139661.html">GitHub上整理的一些工具</a></p>
<p>注意下他的这篇文章是昨天刚刚发布不久的哦：</p>
<p><img src="http://images.cnitblog.com/blog/312243/201412/042337424671608.png" /></p>
<p>哟，这推荐数量还不少呢，我在想<strong>抄袭我文章的那位作者，您不心虚么？？？？</strong></p>
<p>我想说的是，您没有注意到我的文章结尾处有这么一出显著的标记么：</p>
<p><img src="http://images.cnitblog.com/blog/312243/201412/042343360303960.png" /></p>
<h2>目的</h2>
<p>写这篇的文章的目的很简单，就是维护个人的知识成果，也让博客园能更好的给大家营造一个积极向上的写作氛围。</p>
<p>在园子里待的时间也不短了，相信每个人热爱积累和分享的园友，都不希望别人直接把自己的东西拿走当成自己的原创发布到博客园首页上。</p>
<p>哪怕是你转载的时候能随便做到以下几点也行啊：</p>
<ul>
<li>标注这是转载（没有署名也行啊）<br /></li>
<li>对文章内容进行提炼，加入自己的思想<br /></li>
<li>直接转走没关系，至少也尊重下原作者的转载要求吧</li>
</ul>
<p>前阵子有园友反映说自己发表在博客园上的文章被其他网站给抓走了，dudu回复说这种情况博客园也很难去处理，现在没想到自己的文章居然在博客园内被抄袭了，很不爽。</p>
<p>博客园的发文说明也有要求的，那就是<strong>只能</strong>发布原创的：</p>
<p><img src="http://images.cnitblog.com/blog/312243/201412/042354331551572.png" /></p>
<h2>写给抄袭我文章的园友的</h2>
<p>写到这心情也平静了许些，不再像刚才那么气愤了。</p>
<p>希望那位抄袭我文章的园友，看到我的这篇文章后能有所理解，以后不要这么随意的抄袭他人的东西作为自己的原创，这样会打击他人积极性的。</p>
<p>我会联系博客园工作人员将您的文章进行移除的。</p>
<p>以希望您不要太在意此事，以后注意点就好，鼓励分享！</p></div><div id="MySignature"></div>
<div class="clear"></div>
```


