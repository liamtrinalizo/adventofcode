# My Advent of Code solutions
[Advent of Code](https://adventofcode.com/) is an Advent calendar of small programming puzzles.

## Useful shell oneliner
Here are a couple of command lines I use in my workflow
However, I use Zsh and sometime forget what is Bash compatible 😅

If you use them please bear in mind adventofcode creator words:
> Please be careful with automated requests; I'm not a massive company, and I can
> only take so much traffic.  Please be considerate so that everyone gets to play.

Depends on:
    - curl
    - [jq](https://stedolan.github.io/jq/)
    - GNU sort
    - GNU date

### Retrive todays input file
Requires cookie file containing the session id (usually at the repo root)

    curl -b $(cat ../../cookie) https://adventofcode.com/$(date +%Y/day/%-d)/input > input

### Simple list of private leaderboard star scores
Requires cookie file containing the session id and private leaderboard id (if you have one), I usually put them at the repo root

    curl -b $(cat ../../cookie) https://adventofcode.com/2021/leaderboard/private/view/$(cat ../../leaderboard).json | jq '.members[] | [.stars,.name] | @tsv' -r |sort -nr
