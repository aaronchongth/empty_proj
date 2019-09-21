# git workflow

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
