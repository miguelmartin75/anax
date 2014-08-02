Want to get involved with the project? You are free to help out on the project, here are the ways in which you can contribute:

# The code

Before contributing to any of the code, it is
required to read the [coding conventions](#coding-conventions)
of the library and the [sending a pull request](#sending-a-pull-request)
section.

Here is how you can contribute to the code:

- Fix bugs
- Report bugs
- Add/fix documentation
- Implement new features
- Suggest new features

Fixing bugs and implementing new features require for a pull
request to be sent (see below). Adding/fixing documentation
can have a 

## Sending a Pull Request

Since all pull requests for GitHub require
an issue to be opened, I do not mind duplicate
issues for this circumstance (as long as you reference
to the issue you are fixing).

To send a pull request, make sure your code changes
are within another branch. This branch may be based
off of master or develop, or another branch that it is
related to (e.g. experimental branches). Please
see the [other branches section](#other-branches) in [git branches](#git-branches).

## Git Branches

### Main Branches

There are two main branches within the git repository.
These are:

- master
- develop (based off of master)

master is where the latest stable version of the library
is kept. develop is where the next version of the library
is located, and thus is the unstable version; it is not
guarenteed that this branch will compile.

### Other Branches

The other branches are temporary branches related to the library.
There are three types of other branches:

#### Experimental Branches

Experimental branches are for code that is experimental, 
for example trying opitmising some components of the library. 
Experimental branches can be branched off any other branch.

The naming convention for experimental branches is:
`experimental-<name>`, where `<name>` is a name for what
you are experimenting with. 

#### Feature Implementations

Feature implementations are for code that implements a
particular feature. Feature branches *require* to be 
branched off of the develop branch. The naming convention
for a feature branch is `feature-<name>` where `<name>` is
the name of the feature.

#### Patches

Patches, otherwise known as bug fixes, must be based
off of where the bug is present; if the bug is present 
in multiple branches, do the most parent branch. e.g.
if the bug is present in develop and master, branch off
of the master branch. 

The naming conventions for patches is `issue-<X>` where
`<X>` is the number of the issue. If there is no submitted
issue to what you are fixing, then you must submit the issue yourself.

# The [wiki]

You can contribute to the wiki by:

- Creating video/written tutorials; this can be done by:
    - Adding links to tutorials on the [wiki]
    - Writing a tutorial on the [wiki]
- Fixing grammar/spelling in existing articles
- Adding new topics


# Coding Conventions

TODO

[wiki]: https://github.com/miguelmartin75/anax/wiki
[email]: mailto:miguel@miguel-martin.com
