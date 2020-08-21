#!/bin/bash
# Simple script to list version numbers of critical development tools
export LC_ALL=C

VERSION_PLATFORM=$(version -p)
if [ "$VERSION_PLATFORM" = "Portage" ]; then
    echo "Ejecuntado sobre portage."
elif [ "$VERSION_PLATFORM" = "Pacman" ]; then
    echo "Ejecuntado sobre Pacman"
else
    echo "Plataforma desconcida."
    exit 1
fi

version -ci bash g= 3.2
MYSH=$(readlink -f /bin/sh)
echo "/bin/sh -> $MYSH"
echo $MYSH | grep -q bash || echo "ERROR: /bin/sh does not point to bash"
unset MYSH
version -ci binutils  g= 2.25
version -ci bison g= 2.7
if [ -h /usr/bin/yacc ]; then
 echo "/usr/bin/yacc -> `readlink -f /usr/bin/yacc`";
elif [ -x /usr/bin/yacc ]; then
 echo yacc is `/usr/bin/yacc --version | head -n1`
else
 echo "yacc not found"
fi
version -ci bzip2 g= 1.0.4
#echo -n "Coreutils: "; chown --version | head -n1 | cut -d")" -f2
version -ci diffutils g= 2.8.1
version -ci coreutils g= 6.9
version -ci  gawk g= 4.0.1
if [ -h /usr/bin/awk ]; then
 echo "/usr/bin/awk -> `readlink -f /usr/bin/awk`";
elif [ -x /usr/bin/awk ]; then
 echo awk is `/usr/bin/awk --version | head -n1`
else
 echo "awk not found"
fi
if [ "$VERSION_PLATFORM" = "Portage" ]; then
    version -ci gcc-9.2 g= 5.2
elif [ "$VERSION_PLATFORM" = "Pacman" ]; then
    version -ci gcc g= 5.2 
fi
#g++ --version | head -n1
version -ci glibc g= 2.11
version -ci grep g= 2.5.1
version -ci gzip g= 1.3.12
cat /proc/version
version -ci m4 g= 1.4.10
version -ci make g= 4.0
version -ci patch g= 2.5.4
echo Perl $(perl -V:version)
if [ "$VERSION_PLATFORM" = "Portage" ]; then
    version -ci python-3.7 g= 3.0
elif [ "$VERSION_PLATFORM" = "Pacman" ]; then
    version -ci python g= 3.0
fi
version -ci sed g= 4.1.5
version -ci tar g= 1.22
version -ci texinfo g= 4.7
if [ "$VERSION_PLATFORM" = "Portage" ]; then
    version -ci xz-utils g= 5.0.0
elif [ "$VERSION_PLATFORM" = "Pacman" ]; then
    version -ci xz g= 5.0.0
fi

