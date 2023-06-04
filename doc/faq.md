If you have any additions, corrections, ideas, or bug reports please stop by the
Builder Academy at telnet://tbamud.com:9091 or email rumble@tbamud.com -- Rumble

            Frequently Asked Questions (FAQ) for tbaMUD with Answers

This file is intended to cover common questions related to tbaMUD. Any 
contributions and corrections are more than welcome.  It is currently 
maintained by Rumble of the Builder Academy. Please stop by the Builder
Academy if you have any corrections or additions: tbamud.com 9091 
This FAQ was originally written by Ryan Watkins (VampLestat) and later 
maintained by Alex Flectcher (Furry). 

Other great resources are online at: http://tbamud.com
______________________________________________________________________

Table of Contents

1. Introduction
   1.1 I've never played a MUD before.  What should I do?
   1.2 I'm new to C and/or coding. What do I do?
   1.3 I want to build my own MUD.  Where do I start?
   1.4 What is tbaMUD?
   1.5 What is the history of tbaMUD?
   1.6 Where is the original tbaMUD so I can check it out?
   1.7 Will the tbaMUD creators visit my mud?
   1.8 What is UNIX?

2. Resources
   2.1 Where do I find the source code for tbaMUD?
   2.2 Where do I find areas, etc. for tbaMUD?
   2.3 I have questions about tbaMUD.  Where should I go?
   2.4 To what platforms has tbaMUD been ported?
   2.5 How can I submit code or areas for use with tbaMUD?
   2.6 How do I use a patch file and how can I make one?

3. Compiling tbaMUD
   3.1 Why do I get many syntax errors with Sun's ``cc'' compiler?
   3.2 Why do I get all sorts of errors with ``crypt'' functions and header files?
   3.3 When I try to compile, why do I get a lot of undefined symbols
       referenced in comm.o for functions like socket, accept, and bind?
   3.4 Every time I try to compile tbaMUD (or any other piece of software)
       under Linux, it gives me errors and says it cannot find include header
       files in the linux/  and asm/  directories.  What can I do?
   3.5 I'm getting compilation errors from a header file, and I didn't even
       change it?
   3.6 I'm trying to compile the MUD on Windows and am having problems,
       what can I do?
   3.7 How can I do a ``grep'' on Windows?
   3.8 While compiling the MUD, why do I get errors like ``foo.c:1231:
       Undefined symbol `_whereamI' referenced from text segment''
   3.9 What is a parse error and how do I fix it?
   3.10 I have this piece of code that calls bcopy(), bzero(), and bcmp()
        and it won't compile, so what can I do?
   3.11 My compiler doesn't have ``strdup()'', what can I do?
   3.12 I am having trouble with my ``makefile'', what could be the problem?
   3.13 How can I handle directories in C?

4. Running tbaMUD
   4.1 I typed ``autorun'' but then my terminal just froze.
   4.2 I typed ``bin/circle'' and got lots of boot messages, but then it
       said ``Entering game loop'' and froze.
   4.3 Okay, I think the MUD is running but why don't I get a login prompt?
   4.4 How come I get this error when running my MUD: ``Error reading board:
       No such file or directory''
   4.5 I just got this SIGPIPE, what is it and what Can I Do About It?
   4.6 When I run tbaMUD under Linux, it tells me ``gethostbyaddr:
       connection refused'' when the MUD boots, and then dies.  Why?
   4.7 When I run tbaMUD under Windows, it tells me ``Winsock error
       #10047'' when the MUD boots, and then dies.  Why?
   4.8 When I run tbaMUD under Windows, players can't rent---their
       equipment is just dropped on the ground, syslogs don't work, so what
       is the problem?
   4.9 When someone logs on to my Windows MUD, the console screen gives:
       ``gethostbyaddr: No such file or directory''
   4.10 My MUD crashed and my connection got closed.  What can I do?
   4.11 Ok, so how do I use ``gdb''?
   4.12 How can I hunt bugs more effectively?
   4.13 I just added n levels to my MUD (from the stock 34).  How do I set
        my imps up to level n without a pfile wipe?
   4.14 I decided to wipe my pfile away anyway.  What steps should I take to
        do this?
   4.15 I want to expand the ability to pk in my MUD, allowing ASSASSINS
        that'll be able to PK without getting flagged.  How can I do this?
   4.16 Why does it say ``Connection closed by foreign host.'' and not
        display the ``Byebye!'' message I'm trying to send before cutting
        someone off?
   4.17 How do I get the tbaMUD to autoload when the Linux server is
        restarted?
   4.18 My server shuts down my MUD everytime I logoff. How do I keep the
        MUD running when I logoff?

5. tbaMUD Questions
   5.1 Why does tbaMUD use BUF switches all through the code, what's
       happening here?
   5.2 How do I add a new class?  How do I add more levels? etc?

______________________________________________________________________

1.  Introduction

1.1.  I've never played a MUD before.  What should I do?

Don't try to use your own copy of tbaMUD!  There are two levels of MUD users: 
players and administrators.  Administrators do what you're trying to do now -- 
get a copy of a MUD's source code, compile it, and run it. Players use MUDs 
that are being administered by someone else. If you try to actually run a MUD 
before you've ever played one, you'll get very confused indeed! Your best bet 
for now is to play someone else's MUD first.  There are a large number of 
excellent MUDs out there already, some of which are based on tbaMUD code. Check
out other tbaMUD's at: http://www.tbamud.com/forum?c=showthread&ThreadID=86

1.2.  I'm new to C and/or coding.  What do I do?

First, a MUD is not a learning project. It has tens of thousands of lines to 
it, many of which are obscure and unclear to even moderately skilled 
programmers.  Those little, ``Hello, world,'' programs are for learning,
maybe little math tests, etc.  A MUD is a pretty ambitious project to start
with.  That's like trying to run before you can walk, and while there's more
difficult things than a MUD to start with, there's a ton of easier things you 
should start with.  Second, if you are persistent, get a good C reference book 
and read the code, try to comprehend what everything is doing (to some small 
extent).  You should probably avoid comm.c as it is home to the socket 
functions which general C books don't cover and are usually explained in other
books on network programming.  Then try small projects, something similar to 
what already exists.  This way, you can get away with a cut-and-paste job and 
changing some of the code.  Adding a simple version of races isn't all that 
difficult, just examine the class code in class.c and the CON_QCLASS block in 
interpreter.c, cut, paste, and modify.  Also look at structs.h, for "#define 
CLASS_" You'll begin understanding more and more of the code as you copy and 
change it, eventually you'll be able to write a whole function by yourself.  
Spend time learning, going with haste will hurt you more than it will help you.
Many patches and tutorials are available at: http://tbamud.com (such as adding
races, classes, liquids, skills, spells, etc.

1.3.  I want to build my own MUD.  Where do I start?

Many common questions arise from new MUD admins.  It is a good idea to pay
attention to them and take their answers to heart.  These include things
like the following:

I don't have any coding experience with MUDs, but do have a lot of ideas for
my own.  I have played many MUDs for a LONG time, though.

Read the FAQ.  MUD Experience doesn't help a huge amount.  Code experience
does.

I am interested in having a level system of 1-50 mortal and 51-60 imms.  I
am also interested in adding races and classes. How can I accomplish these
things?

By checking out the content at http://www.tbamud.com.

1.4.  What is tbaMUD?

TbaMUD is a DikuMUD derivative, developed by Jeremy Elson as CircleMUD from
Gamma v0.0 of DikuMUD created by Hans Henrik Staerfeldt, Katja Nyboe, Tom 
Madsen, Michael Seifert and Sebastian Hammer at DIKU (Computer Science 
Instutute at Copenhagen University).  Note that CircleMUD is a Diku 
derivative, so its users must follow the DIKU license agreement---most 
notably it cannot be used to make money in ANY way, the original developers' 
names must be in the login screen and that the credits command always presents
the same information, etc.

tbaMUD's vision is to provide the MUDding community a stable and functional 
codebase that includes an in-depth World and help files that makes it ready 
to be molded into a custom MUD by its coders and builders. We also provide 
multiple resources to allow for feedback, contribution, and the sharing of 
ideas within the MUDding community to ensure constant development and 
improvements. 

TbaMUD is highly developed from the programming side, but highly UNdeveloped
on the game-playing side. So, if you're looking for a huge MUD with billions
of spells, skills, classes, and races, tbaMUD will disappoint you. TbaMUD still
has only the 4 original Diku classes, the original spells, and the original 
skills. On the other hand, if you're looking for a highly stable, developed, 
organized, and well documented "blank slate" MUD on which you can put your OWN 
ideas for spells, skills, and classes, then tbaMUD is what what you are looking
for.

1.5.  What is the history of tbaMUD?

TBA stands for The Builder Academy. 

TBA was created in 2000 on Cruel World which was being run by Zemial and Welcor.
I began combining my own experience with the work of others into an extensive 
tutorial zone, help files, and examples. Welcor and I ended up separating TBA 
from Cruel World to further enhance our training of new builders. Welcor has 
taken over the development of Trigedit and has contributed extensively to what
has now evolved into the tbaMUD release. 

After offering several times to take over CircleMUD development TBA released
CircleMUD 3.5 and later changed the codebase name to tbaMUD. TBA now has many
purposes including: Developing trigedit, OLC, the tbaMUD codebase, and all the
zones.

TbaMUD's vision is to provide the MUDding community a stable and functional 
codebase that includes an in-depth World and help files that makes it ready 
to be molded into a custom MUD by its coders and builders. We also provide 
multiple resources to allow for feedback, contribution, and the sharing of 
ideas within the MUDding community to ensure constant development and 
improvements. 

TbaMUD is highly developed from the programming side, but highly UNdeveloped
on the game-playing side. So, if you're looking for a huge MUD with billions
of spells, skills, classes, and races, tbaMUD will disappoint you. TbaMUD still
has only the 4 original Diku classes, the original spells, and the original 
skills. On the other hand, if you're looking for a highly stable, developed, 
organized, and well documented "blank slate" MUD on which you can put your OWN 
ideas for spells, skills, and classes, then tbaMUD is what what you are looking
for.

See release.txt for a release history.

For builders TBA is a low stress, no deadline, training environment. Where 
anyone with motivation can work at their own pace to learn as much or as 
little as they wish. Numerous people are available to answer questions and 
give advice. 1000's of builders served and counting.

1.6.  Where is the original tbaMUD so I can check it out?

The Builder Academy
tbamud.com 9091

1.7   Will the tbaMUD creators visit my mud?

While there is a possibility that one (or more) of the tbaMUD creators will 
drop by your MUD for a visit, to play, or to simply look around, there is a
slim chance that they will identify themselves. We don't want free wizzes 
or favors for our work here.  In fact, we will state categorically that if 
anyone comes on your MUD claiming to be associated with us, they aren't.

1.8.  What is UNIX?

UNIX is not an operating system of itself, it's a type (flavour, if you
will) of operating systems.  Many different kinds of UNIXes exist.  Some of
them are free, some of them are not.  How to tell if you have a UNIX
operating system? Well, UNIXes have the `ps' command, tend to have a `%' or
`#' prompt, give you a home directory, `who' will show who else is on the
system, etc.  Many UNIX systems (such as Linux) strive to be POSIX
compatible, so you'll probably see POSIX mentioned, too.  POSIX is, roughly,
the standards which UNIX operating systems go by.  It says what makes an
operating system part of the UNIX family and so forth.  Some UNIX operating
systems are not 100% POSIX compatible, actually, most aren't.  The following
are types of UNIX (but not all the existing flavours): Linux, FreeBSD, BSD,
BSDi, Solaris.  There are others.  UNIX operating systems are command-based
and Microsoft does not make a variant.

2.  Resources

2.1.  Where do I find the source code for tbaMUD?

TbaMUD's complete source code and areas are available for download at:
http://tbamud.com

2.2.  Where do I find areas, etc. for tbaMUD?

All donated areas have been added to the latest version of tbaMUD. If you
wish to donate some of your own work stop by the Builder Academy.

2.3.  I have questions about tbaMUD.  Where should I go?

Stop by The Builder Academy at tbamud.com 9091 or the website at:
http://tbamud.com

If you have general questions about the MUD such as how to get it running,
how to add new spells, how to add new skills, etc., the first place you
should look is the documentation. `coding.txt' will have information about
how to add new spells, skills, commands, etc. `building.txt' has information
about the World file formats and how to read the files, etc. There are many 
other documents in the doc directory with useful information, read them all.

If you still have questions after reading the documentation, check out:

http://tbaMUD.com/
http://cwg.lazuras.org/modules.php?name=Forums
http://groups.yahoo.com/group/circle-newbies/
http://post.queensu.ca/cgi-bin/listserv/wa?SUBED1=circle&A=1
http://groups.yahoo.com/group/dg_scripts/

2.4.  To what platforms has tbaMUD been ported?

TbaMUD is very portable because it uses the GNU autoconf system, meaning you
only need to type ``configure'' to have it automatically determine various 
features of your system and configure the code accordingly.  TbaMUD compiles
without changes under most BSD and SVR4 systems, including SunOS, Solaris, 
Ultrix, IRIX, AIX, Linux, BSD/OS, HP/UX, and others.

TbaMUD has also been ported to various non-UNIX platforms.  You can now
compile it under OS/2 2.x and 3.x with the OS/2 port of gcc, Windows using 
Microsoft Visual C++ version 4.0 or 5.0, Cygwin, Borland (now Inprise) C++,
Watcom v.11, Cygnus GNU-WIN32, LCC, Macintosh with CodeWarrior, Amiga, and 
Acorn RiscOS.

2.5.  How can I submit code or areas for use with tbaMUD?

Stop by the Builder Academy. tbamud.com 9091 or visit http://tbamud.com

2.6.  How do I use a patch file and how can I make one?

Patch files are created and used via the ``diff'' and ``patch'' utilities,
respectively. These are the various parameters to use with diff (all work in
general on unix based systems, but check out the help entries to be certain.

diff -uN [original_src_directory] [altered_src_directory] > Patch

-u is the unified output. ie. it tells diff to output the text what is
called ``patch'' style.  On some systems, you will have to use -c but it
generates much larger and harder to follow patches.

-N  Tells diff to treat files that are in one directory and not there in the
other as being empty in the one they are not there.  It allows entire files
to be included into the patch.

-r  recursive, add r to the uN above if you want it to recursively add in
any subdirectories.  (be careful with this one)

-p  Tells diff to indicate what function is being ``patched'' in each
section. This may not be supported by all versions of ``diff.''

If you download a patch file and would like to add it to your code, first
make sure to read any instructions that the patch author might have written. 
The command used to add the patch may vary depending on how the patch was
created. This should be given in the first line of the patch or in the
instructions.  Normally, if using GNU patch with a unified diff, the command
should be:

        patch -u < [patchfile]

If the patch was created with a SYSV patcher (i.e. not a unified diff), the
patch should be added with:

        patch -c < [patchfile]

Of course, if the instructions state otherwise, ignore any instructions
given here and follow the instructions given with the patchfile instead.

Finally, in modern patches, there are three characters of interest to note:

o  ! :: The line changes between new and old.
o  + :: This line is added to the old to make the new.
o  - :: This line is removed from the old to make the new.
o  The rest of the lines are just there to give you an idea of where
   to change.

3.  Compiling tbaMUD

3.1.  Why do I get many syntax errors with Sun's ``cc'' compiler?

Because tbaMUD is written in ANSI C, and Sun's standard cc compiler isn't
capable of compiling ANSI C code.  You can try acc, Sun's ANSI C compiler,
but it costs extra money to get it from Sun so your sysadmin may not have
installed it.  Most don't.  The best solution is to get the GCC compiler
from the GNU FTP site (ftp://ftp.gnu.org/pub/gnu) and install it, if you
have enough time and space.

3.2.  Why do I get all sorts of errors with ``crypt'' functions and
      header files?

TbaMUD normally uses the UNIX crypt() function to encrypt players' passwords.
Because of export restrictions imposed by the U.S., some systems do not have
the crypt() function. ``configure'' will usually be able to figure out
whether or not your system has crypt(), but if it guesses incorrectly and
you see problems with the crypt() function or headers, you can manually
disable password encryption by going into the sysdep.h source file and
uncommenting the line that reads:

        #define NOCRYPT

Be warned, however, that doing this causes the MUD to store players'
passwords in plaintext rather than as encrypted strings.  Also, if you move
from a system which has crypt to one that doesn't, players won't be able to
log in with their old passwords!

3.3.  When I try to compile, why do I get a lot of undefined symbols
      referenced in comm.o for functions like socket, accept, and bind?

SVR4 systems require the socket and nsl libraries for network programs.  You
shouldn't see this error any more with version 3.0 because ``configure''
should automatically use those libraries for you; however, if you still have
problems, try adding ``-lsocket -lnsl'' to the line in the Makefile that
links all the object files together into the 'circle' binary.

If you're using V2.20 and you have this error, the best thing to do is
simply to use V3.0 instead.  If you insist on using 2.20, go into the
Makefile and search for the comment next to ``SVR4''.

3.4.  Every time I try to compile tbaMUD (or any other piece of software)
      under Linux, it gives me errors and says it cannot find include header
      files in the linux/ and asm/ directories.  What can I do?

Under Linux, you cannot compile any program unless you install the kernel
source code because the kernel source includes the ANSI C header files.  You
need the files in /usr/include/linux, which are distributed separately from
the rest of /usr/include.

The easiest way to do this if you're using the Slackware Linux distribution
is simply to install the 'K' series of disks which is the kernel source.

Otherwise, you'll have to set up your include files manually. The easiest
way to get these is to download kernel source from:

http://www.kernel.org/mirrors/

Get the kernel source that matches the kernel you're running (type `uname
-a' to find your kernel version).  Then unpack the kernel into the usr/src
/directory.  It's about 13 megabytes compressed and 54 megabytes
uncompressed (For the 2.2.9 kernel).

Read the README file that comes with the kernel, and make the symbolic links
you need for /usr/include/asm and /usr/include/linux.

Now compile the MUD.  This will take care of most of the errors.  You may
have to do `make config' and `make dep' in /usr/src/linux as well, in order
to make linux/config.h and other files that get generated by these steps.

You can remove the whole kernel source tree except for include/ at
this point and get most of your 48.5 megs back.

(Thanks to Michael Chastain for providing this answer.)

3.5.  I'm getting compilation errors from a header file, and I didn't even
      change it?

Okay, if you really didn't change ``structs.h'' then the error isn't in
``structs.h''.  I think I've seen 2 cases where this has happened, the
first, is that the header file you included right before the header file
messing has an error in it.  I can't really say much beyond that, but look
for a missing semicolon, are any other errors you can find.

If you include files out of order, it can mess things up.  For example, B.h
has stuff in it that is defined in A.h, and if you include B.h before A.h,
you can get errors, your best bet here is to mess with the order of the
headers, making sure you put ``conf.h'' and ``sysdep.h'' at the top,
followed by ``structs.h'', ``utils.h'', etc. Any file specific headers
should be the last one included just for coding style.

3.6.  I'm trying to compile the mud on Windows and am having problems,
      what can I do?

The first thing to do is to make sure you are compiling a recent version of
the source code.  Patch Level 11 and onwards all support Windows winsock
sockets now.  Second, you should ensure that you have carefully read the
README.WIN file for instructions on what to include.  Next, ensure that you
are using a C compiler that supports long filenames (for example, MSVC 4.0
does, MSVC 1.0 does not).  If you happen to be trying to patch something
into your code, you should use patch for DOS
(ftp://204.119.24.14/pub/patch/patch12.zip).  This does not support long
filenames (but can be used with short filenames).

3.7.  How can I do a ``grep'' on Windows?

1. Select ``start menu''->``find''->``files or folders''
2. Enter the files/dirs to search in.
3. Select ``Advanced''
4. In the ``Containing Text'' input box, type in the text you want.
5. Double click on a match to bring up the file that matched.
   Even better is to use MSVC's find command (if you have it).

3.8.  While compiling the mud, why do I get errors like ``foo.c:1231:
      Undefined symbol `_whereamI' referenced from text segment''

You forgot to include a source file into the make.  Go edit your Makefile
and make sure all the necessary *.c files are in there, in particular,
whichever C file defines the function that the compiler is complaining is
undefined.  If all else fails, try deleting all the *.o files and
recompiling from scratch.

3.9.  What is a parse error and how do I fix it?

A parsing error is often a missing or extra semicolon, parenthesis, or
bracket ({).

If the parse error is before a semicolon at the end of a line of code, it is
something on that line.

If it is at the beginning of a line within a function, it is usually a
missing semicolon on the previous line.

If it is at the beginning of a function, count your brackets (especially the
{} ones) in the previous function.

I can't think of any other parse errors.  These are the ones I commonly see. 
With a bit of practice, they are very easy to locate and fix.  For a more
detailed explanation, check out the C Language FAQ.

3.10.  I have this piece of code that calls bcopy(), bzero(), and bcmp() and
       it won't compile, so what can I do?

All three of these functions are fairly standard on BSD systems. However,
they are not considered to be very portable, and thus should be redefined. 
For example, the equivalents for SYSV are:

#define bcopy(from,to,len)      memmove(to,from,len)
#define bzero(mem,len)          memset(mem,0,len)
#define bcmp(a,b,len)           memcmp(a,b,len)

3.11.  My compiler doesn't have ``strdup()'', what can I do?

Use tbaMUD's built-in str_dup() function instead.

3.12.  I am having trouble with my ``makefile'', what could be the problem?

If you used cut and paste to insert items into your makefile, it is likely
that you accidentally put spaces at the beginning of lines where tabs are
needed.  This is how the makefile must be constructed:

foo.o: foo.c conf.h sysdep.h structs.h utils.h interpreter.h \
  handler.h db.h
{TAB}$(CC) -c $(CFLAGS)

To add these lines properly, you can use gcc to assist you with the
following shell script (from Daniel Koepke):

#!/bin/sh
gcc -MM $1 >> Makefile
echo "{TAB}\$(CC) -c \$(CFLAGS) $1" >> Makefile

To use this script, replace {TAB} with a tab, and then run the script
like: add_file foo.c

3.13.  How can I handle directories in C?

Note that this seems only to be valid for UNIX OSes.  Handling of
directories is accomplished through the dirent.h and sys/types.h files.  The
function opendir() returns a ``DIR*'' pointer (it's like but not the same as
the ``FILE *'' pointer) when you pass it the name of a directory to open or
NULL if it can't open the dir.  After the directory has been opened, you can
step through the files or search for particular files, etc. using readdir(),
seekdir(), and scandir(). When you reach the end of the directory list, you
can either go back to the start with rewinddir() or close the directory with
closedir(). The following code (which has not been tested) should open a
directory and go through it one by one and prints the filenames:

  struct dirent * ffile;
  DIR * my_dir;

  if (!(my_dir = opendir("foo")))
    return;

  while (1) {
    if (!(dirent = readdir(my_dir)))
      break;
    printf("%s\n", dirent->d_name);
  }

  closedir(my_dir);

The dirent structure contains only two useful elements, the file's name
(d_name) and the files length (d_reclen).

Thanks to Daniel Koepke for the above.

4.  Running tbaMUD

4.1.  I typed ``autorun'' but then my terminal just froze.

autorun is a script which automatically runs, logs, and reboots the game for
long-term runs.  You should run autorun in the background by typing
``./autorun &'' -- the MUD will start running in the background and you'll
get the normal UNIX prompt back immediately (see section 4.3). The game will
then run unattended until you explicitly shut it down.

On some systems, you may need to prepend ``nohup'' to the autorun command
since some systems will kill off any processes left running when you leave
the shell.

4.2.  I typed ``bin/circle'' and got lots of boot messages, but then it said
      ``Entering game loop'' and froze.

It is not frozen, it is just waiting for people to connect.  You have to run
the MUD in the background by typing ``autorun &'' and then use telnet to
connect to the game (see next section).

4.3.  Okay, I think the MUD is running but why don't I get a login prompt?

In order to play the MUD, you must connect to it using the telnet command,
i.e. ``telnet localhost 4000''.

4.4.  How come I get this error when running my mud: ``Error reading board:
      No such file or directory''

This is not a bad thing, all it means is that you have some boards on the
mud and that it can't find the file for them.  Since it can't find the file,
the mud will just create the file on the fly and use that, so the next time
something is posted to the board, the files will exist.  However, if you did
have files for the boards and you are suddenly getting this error, it means
that the board files have been deleted or something similar.

4.5.  I just got this SIGPIPE, what is it and what Can I Do About It?

Often it appears that other people send your system SIGPIPEs when their
connection is closed, in fact, it is not the person sending the SIGPIPE, it
is your system.  The SIGPIPE is generated when your program attempts to
write to descriptor which has no one listening to it.  This occurs if the
character is sent a message by the mud after connecting, but before the
socket is flagged with an exception or reads 0 bytes.  By default, tbaMUD
ignores these SIGPIPEs, with the line my_signal(SIGPIPE, SIG_IGN) in
signal_setup().  Where most people see the problems with SIGPIPE is while
debugging with GDB.  By default, GDB responds to a SIGPIPE by stopping the
program, printing that a SIGPIPE was received, and passing it to the
program.  You can change the action taken by GDB by using the `handle'
command. To stop the program from stopping at SIGPIPE, you would give GDB the
command `handle SIGPIPE nostop'

4.6.  When I run tbaMUD under Linux, it tells me ``gethostbyaddr: con-
      nection refused'' when the MUD boots, and then dies.  Why?

You need to make sure you have Networking and TCP/IP support compiled into
your Linux kernel, even if you aren't actually connected to the Internet. 
The easiest way to do this if you're using Slackware is to install one of
Slackware's precompiled networking kernels.  Also, make sure to install
Slackware's `N' series of disks which contains other networking support
files.

If Slackware's precompiled kernel isn't available you'll have to compile the
kernel yourself.  First make sure the kernel source is installed in
/usr/src/linux (see section 3.1.4) and follow the instructions in
/usr/src/linux/README. When you do `make config' it will ask you a series of
questions about which kernel features you want; make sure to answer ``Y'' to
``Networking support'' and ``TCP/IP support''.

4.7.  When I run tbaMUD under Windows, it tells me ``Winsock error
      #10047'' when the MUD boots, and then dies.  Why?

You need to configure TCP/IP networking from the Network Control Panel, even
if you are not connected to the Internet.  From the Network Control Panel,
select ``Add Protocol'', and under the vendor ``Microsoft'', choose
``TCP/IP''.  It may ask you to insert the Windows CDROM in order to copy
the drivers onto your hard drive.

4.8.  When I run tbaMUD under Windows, players can't rent---their
      equipment is just dropped on the ground, syslogs don't work, so what
      is the problem?

The reason that objects aren't saved when your players quit is that certain
unzip programs are buggy and don't completely recreate the MUD's directory
structure (in particular, it doesn't create directories which have no files
in them.) This is fixed in Circle 3.0 patchlevel 12 and above.  Before
patchlevel 12, you can fix it simply by manually creating the needed
directories:

        CD \tbamud
        cd lib\plrobjs
        mkdir A-E
        mkdir F-J
        mkdir K-O
        mkdir P-T
        mkdir U-Z
        mkdir ZZZ

Object saving should then work.  The syslogs are a different story; no data
is written to the system logs because the code currently is configured
simply to write all errors to the standard error file descriptor (stderr),
and Windows doesn't seem to let you redirect stderr to a file the same way
UNIX does.  pl12 allows you to direct logs to a specific file instead.

4.9.  When someone logs on to my Windows MUD, the console screen
gives: ``gethostbyaddr: No such file or directory''

This means the MUD can't resolve the IP address of the connecting player's
source site into a hostname.  You probably don't have DNS correctly
configured in the Windows Network Control Panel menu (under configuration of
the TCP protocol).  Make sure you have the IP address of your ISP's DNS
server listed.

4.10.  My MUD crashed and my connection got closed.  What can I do?

Just because your connection got closed from the MUD (for example, if you
get too much information sent to you and the telnet session gets closed),
this doesn't always mean that the game itself crashed. Before reporting
something as a crash bug, make sure that the game itself crashed, and above
all, try to duplicate the circumstances before reporting it as a crash bug. 
You can also try using gdb to find out why the MUD is crashing if it gives
you a core dump.

4.11.  Ok, so how do I use ``gdb''?
4.12.  How can I hunt bugs more effectively?

See debugginge.txt
 
4.13.  I just added n levels to my MUD (from the stock 34).  How do I set my
       imps up to level n without a pfile wipe?

This should no longer be a problem with the do_cheat function in act.wizard.c
but the only ID with access by default is IDNUM 1.

4.14.  I decided to wipe my pfile away anyway.  What steps should I take to
       do this?

tbaMUD has ASCII pfiles so all you have to do is delete the index and all 
pfiles in the /lib/plrfiles/ directory.

You should also remove files in plrobjs, plralias, and plrvars, unless you want
the recreated characters to come back with their same equipment, aliases, and
trigger variables.

4.15.  I want to expand the ability to pk in my MUD, allowing ASSASSINS
       that'll be able to PK without getting flagged.  How can I do this?

With tbaMUD simply enter Cedit (configuration editor) and select Game Play 
Options. Then enable Player Killing.

4.16.  Why does it say ``Connection closed by foreign host.'' and not
       display the ``Byebye!'' message I'm trying to send before cutting
       someone off?

This usually happens if you are doing something like this:

  send_to_char(ch, "Bye bye.  Come back soon, ya hear?");
  close_socket(ch->desc);

The close_socket immediately dispatches/closes the connection, while
send_to_char puts the message on the output queue to be dispatched next
game_loop cycle. Therefore, the socket is gone.  On some systems (ie old
linux), this can even cause a infinite loop attempting to write to a closed
socket. The proper way of doing this and other ``Byebye'' messages is to set
the CON state of the player to CLOSE, like this:

  send_to_char(ch, "Bye bye.  Come back soon, ya hear?");
  STATE(ch->desc) = CON_CLOSED;

This will then cycle to the next game_loop, dispatch the output queues
(therefore sending the byebye message) and then close the socket. Further
note, in some bizarre cases, this only seems to send about 40 characters and
no escape codes.  Sending more than 40 characters or escape codes (like the
clear screen sequence) will crash the process reporting a problem similar to
writing to a closed socket.

4.17.  How do I get the tbaMUD to autoload when the Linux server is
       restarted?

In /etc/rc.d/rc.local find where things like sendmail and (maybe) gpm
are started.  Add something like:

cd /home/mudlogin/tbamud/
su mudlogin -c ./autorun &
cd

Of course, change the "mudlogin" to whatever the name of the account is that
normally has control of the MUD, and change the path in the first cd to
whereever the MUD is run from.

For more info: man su

4.18.  My server shuts down my MUD everytime I logoff. How do I keep the MUD
       running when I logoff?

Instead of typing "autorun &" to start the autorun script (which starts and
keeps the MUD running), type "nohup autorun &".  Running the autorun via
nohup will keep the script and the MUD running when you logoff of the
server. For more information type "man nohup" at the prompt on your server.

5.  tbaMUD 3.X

5.1.  Why does tbaMUD use BUF switches all through the code, what's
      happening here?

From Jeremy:

This code is the new output buffering system that I wrote for Circle in the
early (non-released) beta versions of 3.0.  The old Diku code for queueing
output (which stayed with Circle until version 2.20) was memory- and
time-inefficient in many cases (and, in my opinion, was inefficient for the
normal behavior of most MUDs).

First, I should explain what output queueing is and why it is necessary.  On
each pass through the game_loop(), the MUD performs a number of steps: check
to see if there are any new players connecting, kick out people with bad
links, read input over the network for all players, then process the input
for each player that has sent a complete line over the net.  The processing
step is usually where output is generated because it is where MUD commands
are processed (e.g., ``kill'' might generate output of ``Kill who?'') When
output is generated, it is not immediately sent out to the player, but
instead queued for output in a buffer.  After all players' commands are
processed (and each command generates the appropriate output for various
players), the next step of the game_loop() is to send all the queued output
out over the network.

The new output system that tba now uses allocates a small, fixed size
buffer (1024 bytes) for each descriptor in which output can be queued.  When
output is generated (via such functions as send_to_char(), act(), etc.), it
is written to the fixed size buffer until the buffer fills.  When the buffer
fills, we switch over to a larger (12K) buffer instead.  A ``buffer
switch'', therefore, is when the 1024-byte fixed buffer overflows.

When a large (12K) buffer is needed, it is taken from a pool of 12K buffers
that already been created.  It is used for the duration of that pass through
the game_loop() and then returned to the pool immediately afterwards, when
the output is sent to the descriptor.  If a large buffer is needed but none
are in the pool, one is created (thereby increasing the size of the pool);
the ``buf_largecount'' variable records the current pool size.

If a player has already gone from their small to large buffer, and so much
output is generated that it fills even the large buffer, the descriptor is
changed to the overflow state, meaning that all future output for the
duration of the current pass through the game loop is discarded.  This is a
buffer overflow, and the only state in which output is lost.

Now that I've described how the system works, I'll describe the rationale. 
The main purpose for the two-tiered buffer system is to save memory and
reduce CPU usage.  From a memory standpoint: Allocating a fixed 12K buffer
for each socket is a simple scheme (and very easy to code), but on a large
MUD, 100 12K buffers can add up to a lot of wasted memory.  (1.2 megs of
memory used for buffering on a 100-player MUD may not seem like very much,
but keep in mind that one of tba's big selling points several years ago,
when memory was expensive, was that it had a very small memory footprint (3
or 4 megs total!) And from a CPU standpoint: the original Diku used a
dynamically allocated buffer scheme to queue output, which unfortunately
meant that for each player, on each pass through the game loop, dozens of
tiny buffers (often one for every line of output, depending on the code to
execute the command) were allocated with malloc(), individually written to
the system using individual calls to write(), and then free()'d.  My system
saves hundreds or thousands of calls per second to malloc() and free(), and
reduces the number of system calls *drastically* (to at most one per player
per pass through the game loop).

The trick is to choose the size of the small and large buffers correctly in
order to find the optimal behavior.  I consider ``optimal'' to mean that 90%
of the time, most players stay within the limits of their small buffer (for
example, when wandering through town or mindlessly killing some monster
while watching damage messages go by).  Hopefully, a large buffer switch is
only necessary when a player executes a special command that generates an
unusually large amount of output, such as ``who'', ``read board'', or
``where sword''.  This critically depends on the fact that not everyone will
be executing such a special large-output command at the same instant.

For example, imagine you have 10 players on your MUD.  They are all
wandering around town, and every once in a while one of them types ``who'',
or reads the board, meaning that they are seeing more than 1024 bytes of
output at a time.  On such a MUD, I would hope that there would only be a
single 12K buffer allocated which gets passed around among all the 10
players as needed.  Now, all players think they can queue up to 12K of
output per command without getting truncated even though only one 12K buffer
actually exists -- they are all sharing it.

But - there's a problem with this.  There are certain cases when many
players have to see a lot of output at the same instant (i.e. on the same
pass through the game_loop()), all of them will need a large buffer at the
same time and the pool will get very big.  For example, if an evil god types
``force all who''; or if the MUD lags for several seconds, then suddenly
gets unlagged causing many commands to be processed at the same moment; or
if 20 people are all trying to kill the same MOB and are all seeing 20
damage messages (more than 1024 bytes) on the same pass through the
game_loop().

Unfortunately, the current patchlevel of tba has no way to destroy large
buffers so such cases are pathological and cause wasted memory.
Unfortunately since I don't run a MUD I can't actually tell how often this
happens on a real MUD.  (If there are any IMPs out there who run large MUDs
(say, >= 30-50 players on regularly), and you've read this far, please send
me the output of ``show stats'' after your MUD has been played for at least
several hours.)

5.2  How do I add a new class?  How do I add more levels? etc?

Many common questions about basic additions are answered here:
http://tbamud.com