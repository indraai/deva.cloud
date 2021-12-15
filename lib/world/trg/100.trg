#1000
Gunnar Larsen~
0 g 100
~
  wait 5s
  say Well?
  wait 2s
  say Any Radar return?
~
#1001
James Sneed Trigger~
0 g 100
~
  wait 6s
  emote looks up, a broad smile on his face.
  say This is it, friends—the Bottomless Crevasse.
  wait 4s
  emote shakes head
  say None.
  *set time after 10s here
~
#1002
Hash Tracker~
1 acg 100
n~
wait 2s
You are in %actor.room.vnum% currently.
~
#1003
Underground Kingdom Guide~
0 b 100
~
set fol %self.follower%
set inroom %self.room.vnum%
set startroom 1000
if %fol%
  if %inroom% == %startroom%
    wait 5 sec
    north
  else
    wait 60 sec
    %random.dir%
  end
else
  if %inroom% != %startroom%
    %mgoto% 1000
  end
end
~
#1005
Room 1005 Trigger~
2 g 100
~
set thetoken %actor.inventory(200)%
set thisroom %self.vnum%
%echo% the room is %thisroom%
if %thetoken%
  %door% %thisroom% north flags abcd
  %door% %thisroom% north key 1013
end
~
#1008
R1008 Give Token~
2 g 100
~
set thekey 1008
set thetoken %actor.inventory(%thekey%)%
set thisroom %self.room.vnum%
set reward 50
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1010
R1010 Check Token~
2 g 100
~
set thetoken %actor.inventory(1008)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% north purge
end
~
#1012
R1012 Check Token~
2 g 100
~
set thetoken %actor.inventory(1020)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1013
R1013 Give Token~
2 g 100
~
set thekey 1013
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 60
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1016
R1016 Check Token~
2 g 100
~
set thetoken %actor.inventory(1023)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1020
R1020 Give Token~
2 g 100
~
set thekey 1020
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 50
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1021
RM1021~
2 g 100
~
set thetoken %actor.inventory(1032)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% north purge
end
~
#1023
R1023 Give Token~
2 g 100
~
set thekey 1023
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 100
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1024
R1024 Give Token~
2 g 100
~
set thekey 1024
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 30
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1026
RM1026~
2 g 100
~
set thetoken %actor.inventory(1024)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1032
R1032 Give Token~
2 g 100
~
set thekey 1032
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 10
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1033
R1033 Give Token~
2 g 100
~
set thekey 1033
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 10
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1037
RM1037~
2 g 100
~
set thetoken %actor.inventory(1047)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% north purge
end
~
#1039
RM1039~
2 g 100
~
set thetoken %actor.inventory(1047)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1044
RM1039~
2 g 100
~
set thetoken %actor.inventory(1023)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% north purge
end
~
#1047
R1047 Give Token~
2 g 100
~
set thekey 1047
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 10
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1051
RM1051~
2 g 100
~
set thetoken %actor.inventory(1064)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1053
RM1053~
2 g 100
~
set thetoken %actor.inventory(1060)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% north purge
end
~
#1055
RM1055~
2 g 100
~
set thetoken %actor.inventory(1062)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1058
RM1058~
2 g 100
~
set thetoken %actor.inventory(1072)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1060
R1060 Give Token~
2 g 100
~
set thekey 1060
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 10
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1062
R1062 Give Token~
2 g 100
~
set thekey 1062
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 10
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1064
R1064 Give Token~
2 g 100
~
set thekey 1064
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 10
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1065
R1065 Give Token~
2 g 100
~
set thekey 1065
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 10
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1068
RM1068~
2 g 100
~
set thetoken %actor.inventory(1072)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1069
R1069 Give Token~
2 g 100
~
set thekey 1069
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 50
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1070
RM1070~
2 g 100
~
set thetoken %actor.inventory(1084)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% north purge
end
~
#1072
R1072 Give Token~
2 g 100
~
set thekey 1072
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 50
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1074
R1074 Give Token~
2 g 100
~
set thekey 1074
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 100
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj 1008 %actor%
  %send% %actor% key:You earn the 0x1074 Token Key.
end
~
#1075
Professor Bruckner~
0 g 100
~
wait 2s
emote fills his pipe with tobacco.
wait 2s
say As I explained it's a Black Hole in the center of the Earth.
wait 2s
emote lights his pipe
wait 2s
say Who will volunteer to come with me?
~
#1077
RM1077~
2 g 100
~
set thetoken %actor.inventory(1033)%
set thisroom %actor.room.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1078
RM1078~
2 g 100
~
set thetoken %actor.inventory(1074)%
set thisroom %self.vnum%
if %thetoken%
  %door% %thisroom% south purge
end
~
#1084
R1084 Give Token~
2 g 100
~
set thekey 1084
set thetoken %actor.inventory(%thekey%)%
set thisroom %self.vnum%
set reward 100
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1089
R1089 Give Token~
2 g 100
~
set thekey 1089
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 100
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1102
R1102 Give Token~
2 g 100
~
set thekey 1102
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 100
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1103
R1103 Give Token~
2 g 100
~
set thekey 1103
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 2000
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1106
R1106 Give Token~
2 g 100
~
set thekey 1106
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 1000
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
#1108
R1108 Give Token~
2 g 100
~
set thekey 1108
set thetoken %actor.inventory(%thekey%)%
set thisroom %actor.room.vnum%
set reward 1000
if !%thetoken%
  wait 1s
  nop %actor.exp(%reward%)%
  %send% %actor% exp:You earn %reward% EXP for your efforts.
  wait 1s
  nop %actor.gold(%reward%)%
  %send% %actor% gold:You earn %reward% GOLD for a job well done.
  wait 1s
  %load% obj %thekey% %actor%
  %send% %actor% key:You earn the 0x%thekey% Token Key.
end
~
$~
