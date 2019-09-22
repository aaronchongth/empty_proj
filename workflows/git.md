# git workflow :hammer:

Parts of the documentation may only be applicable to `github`, but `git` commands in general should be universal.

## tl;dr

* Development workflow

```bash
git clone https://<repo url>                                # public repository
git clone ssh://git@github.com/<repo owner>/<repo name>     # private repository with access

git checkout -b new-feature-branch                          # starting development on new feature branch

git add -A                                                  # if you are certain everything should be commited
git add <specific paths>                                    # only for commiting specific items
git commit -m "<commit text> <commit emoticon>"             # emoticons should be mandatory

git push                                                    # push to the remote repository
```

* preparing for pull request, merging will allow you to run regression tests so you don't break stuff

```bash
git checkout master
git pull
git checkout <new feature branch>
git merge master

# resolve conflicts

git push
```

## notes

* conflicts can be easily resolved using tools or IDEs, Visual Studio code has a nice interface for it

* `master` branches are normally push protected, but it is good practice to check and make sure remote pushes don't go directly to `master`. Disastrous things may happen otherwise :boom:

* use a combination of `issues` and `gist.github.com` to raise bugs or concerns to the developers, always include instructions to replicate the problem, build instructions and all other relevant information

## readme

READMEs are mostly written in `markdown`, but may include `html` as well. No `css` though, to prevent any unwanted code injection, the `github` team has written a `sanitizer` which strips the `.md` file and leaves only the allowed elements and attributes behind. More information can be gathered from these two sources,

* https://github.com/github/markup/issues/119
* https://github.com/jch/html-pipeline/blob/master/lib/html/pipeline/sanitization_filter.rb

`README`s should include some form of 

* description
* results or benchmarks
* installation, build instructions
* example applications
* general notes for end-users (or for contributing)
