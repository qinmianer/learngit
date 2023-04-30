# Commands

**config**

[Git - 初次运行 Git 前的配置](https://git-scm.com/book/zh/v2/起步-初次运行-Git-前的配置

在命令行中配置某些信息：

```console
$ git config --global user.name "John Doe"
$ git config --global user.email johndoe@example.com
$ git config --list [--show-origin]  
# 进入某个repo后，查看所有Git当时能找到的配置 --list可简写成-l,
# 查看配置信息的来源文件
$ git config <key> # 来检查 Git 的某一项配置
```

配置信息存放在三个文件：

系统级别：`/etc/gitconfig` 文件包含系统上每一个用户及他们仓库的通用配置。用--system选项

用户级别：`~/.gitconfig` 文件只针对当前用户，用--global选项（用的最多）

项目级别：当前git仓库下`.git/config`仅针对该仓库，用--local选项

**初始化git仓库的方式**

- 进入项目目录，`git init`,  但是，在这个时候，仅仅是做了一个初始化的操作(创建了.git文件夹)，你的项目里的文件还没有被跟踪。

- git clone <url>
  
  支持HTTPS：`git clone https://github.com/user/repo.git`
  
  支持SSH：`git clone git@github.com:user/repo.git` (有时候HTTPS不行，用SSH会很管用)
  
  支持Git协议：`git clone git://example.com/user/repo.git`

**The .gitignore file**

`.gitignore` 文件中指定不需要追踪的文件或文件夹（让他们对git不可见）

github.com/github/gitignore

**status**

`git status (-s)` 查看所有文件状态(-s显示简单的概述)：包括工作区和暂存区的差异(没有执行git add的文件, 包括修改、新增、删除的文件), 暂存区未执行commit的文件：

总的来说工作目录下的每一个文件都不外乎这两种状态：**已跟踪** 或 **未跟踪**，已跟踪是已经纳入版本控制的文件。未跟踪的文件会提示：

Untracked files: (use "git add <file>..." to include in what will be committed)

已跟踪的文件状态有可能有几种情况：

- 修改了但是没有加入index（暂存区）: 
  
  Changes not staged for commit:
  
    (use "git add <file>..." to update what will be committed)
  
    (use "git restore <file>..." to discard changes in working directory)
  
          modified:   hello.cpp

- 删除了但是没有加入index：【修改和删除后add和restore是一致的】
  
  Changes not staged for commit:
  
    (use "git add/rm <file>..." to update what will be committed)
  
    (use "git restore <file>..." to discard changes in working directory)
  
          deleted:    file2.txt

- 暂存区未执行commit的文件
  
  Changes to be committed:
  
    (use "git restore --staged <file>..." to unstage)
  
          modified:   hello.cpp

**add命令**

`git add [file-name1] [file-name2]`  将修改的文件从workspace(工作区)添加到index(索引/暂存区)

`git add .`  将工作区修改和新增的文件添加到暂存区，不包括删除的文件

`git add -u` update tracked files

`git add -A`  add changes from all tracked and untracked files

**git diff**

`git diff [filename]` 指定具体的文件就只查看这个文件，否则查看所有文件差异

不带参数，显示工作区文件与暂存区中最近的一次文件快照的差异

`git diff --staged`带参数的，显示的是staged between last commit

例：某文件修改1次，git add暂存，又修改1次，git diff只能看修改2，git diff --staged只能看修改1

（个人感觉用git diff查看文件差异不太方便，<u>在IDE中使用Git diff</u>）

**git restore撤销修改**

场景1：丢弃工作区的修改：discard changes in working directory

`git restore <file>... / git checkout -- <file>...`

if 修改后还没有被放到暂存区，撤销修改就回到和版本库一模一样的状态；

if 已经添加到暂存区后，又作了修改，撤销修改就回到添加到暂存区后的状态。

总之，就是让这个文件回到最近一次`git commit`或`git add`时的状态。

场景2：撤销暂存 (unstage)

`git restore --staged <file> / git reset HEAD <file>`

**删除文件**

在工作区删除文件之后，删除也算作修改，用git status查看，显示：

Changes not staged for commit:

  (use "git add/rm <file>..." to update what will be committed)

  (use "git restore <file>..." to discard changes in working directory)

 deleted:    file1.txt

要把删除文件的操作添加到暂存区，用git add/rm file是等效的，然后再通过git commit提交

**重命名文件**

 要在 Git 中对文件改名，可以这么做：`git mv file_from file_to` 相当于：

`mv file_from file_to; git rm file_from; git add file_to`

如果是在外部软件中对文件改了名，记得把后两条命令执行一下

**commit命令**

`git commit -m [message]` 将暂存区所有文件添加到本地仓库

`git commit [file-name1] [file-name2] -m [message]` 将暂存区指定文件添加到本地仓库

`git commit -am [message]` 将工作区内容直接添加到本地仓库

`git commit --amend` 快速将当前文件修改合并到最新的commit，不会产生新commit。

例如，你提交后发现忘记了暂存某些需要的修改，可以像下面这样操作：

```console
$ git commit -m 'initial commit'
$ git add forgotten_file
$ git commit --amend
```

最终你只会有一个提交——第二次提交将代替第一次提交的结果。

**log**

`git log` 显示所有commit日志，即commit历史记录

`git log --pretty=oneline` 将每条日志单行显示

`git log -n` 显示最近的n条记录

**reflog**

`git reflog` 显示操作本地版本库的命令，包括commit和reset。在回退版本后，找不到commit id了可用此命令查看历史

**版本回退**

`HEAD`是指向当前所在分支最新提交的指针。

`git reset --hard HEAD^` 或 `git reset --hard HEAD^^`回退到上一版本、上上一

`git reset --hard <commit id>` 回退或恢复到指定的commit

版本回退后后悔了，想要恢复，可借助git reflog查看引用历史

**远程仓库**

添加远程仓库（**必须在一个有.git的项目目录下**）：

-  `git remote add <shortname> <url>`, shortname是别名。例如`git remote add pb https://github.com/paulboone/ticgit`

- 一个repo目录下，可以有多个远程仓库。**你使用 clone命令克隆了一个仓库，命令会自动将其添加为远程仓库并默认以 “origin” 为简写。**

- `git remote` 显示所有的远程仓库简写（必须在一个有.git的项目目录下）

从远程仓库中抓取与拉取：

`git fectch <remote_name>` 抓取克隆（或上一次抓取）后新推送的所有工作。

推送到远程仓库：

`git push <remote_name> <branch_name>`. 例如git push origin master

 查看一个远程仓库更多信息：

`git remote show <remote_name>`

远程仓库重名名与移除：

`git remote rename pb pual`

`git remote remove paul` 

**标签**

列出标签: `git tag [-l "通配符"]`

创建标签（默认是为最新的commit打标签）：

- 创建附注标签：`git tag -a <label> -m <message>`

- 创建轻量级标签：`git tag <label>` 

- 区别：附注标签是存储在 Git 数据库中的一个完整对象， 它们是可以被校验的，其中包含打标签者的名字、电子邮件地址、日期时间， 此外还有一个标签信息，并且可以使用 GNU Privacy Guard （GPG）签名并验证。 通常会建议创建附注标签。

为历史commit打标签：`git tag -a xxx -m xxx <commit id>` 

推送标签到远程仓库：`git push origin v1.5` or `git push origin --tags`推送一个本地标签或推送全部未推送的本地标签

删除一个本地标签 `git tag -d <tagname>`

删除一个远程标签 `git push origin :refs/tags/<tagname>`可以删除一个远程标签。
