# Initialise a template for a problem resolution.
# usage : init.sh <N> <NAME>
# N : the number of the problem, e.g. 1
# NAME : the name of the problem, e.g. array_sorting
# instance "55" for "problem_55"
problem_number=$1
# a string, the problem name, for 
# instance "jump_game" for 
# "problem_XX_jump_game"
problem_name=$2

# problem directory
dir="problem_${1}_${2}"
mkdir -p $dir

# build.sh
file_build="$dir/build.sh"
touch $file_build
echo -e $'g++ -std=c++2a \
    -O3 \
    -Wall \
    -Wextra \
    -Werror \
    -Wfatal-errors \
    -pedantic \
    -pg \
    -o problem_${problem_number} ./problem_${problem_number}.cpp' \
    > $file_build
chmod u+x $file_build

# C++ file
file_cpp="$dir/problem_${problem_number}.cpp"
touch $file_cpp
echo -e $'/*
Insert description
*/

#include <iostream>
#include <vector>


std::ostream& operator << (std::ostream& stream,
                           const std::vector<int>& v)
{
    for(const auto& x : v)
    {   stream << x << \" \" ; }
    return stream ;
}


class Solution
{
    public:
    /* insert solution */
} ;


int main()
{
    Solution s ;
    /* insert tests */
    return 0 ;
} ;' \
> $file_cpp


# Python file
file_py="$dir/problem_${problem_number}.py"
touch $file_py
echo -e $'"""
Insert description
"""

import typing as tp


if __name__ == "__main__":

    s = Solution()

' \
> $file_py