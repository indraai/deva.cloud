#3100
North: Agency Guard~
2 q 100
~
set vnum %self.vnum%
set secstr %vnum%:%actor.id%:%direction%
%echoaround% security:check:%secstr%
if %direction% == north && %actor.is_pc%
  %send% %actor% Access Denied
  %echoaround% security:deny:%secstr%
  return 0
else
  %echoaround% security:allow:%secstr%
end
~
#3101
East: Agency Guard~
2 q 100
~
set vnum %self.vnum%
set secstr %vnum%:%actor.id%:%direction%
%echoaround% security:check:%secstr%
if %direction% == east && %actor.is_pc%
  %send% %actor% Access Denied
  %echoaround% security:deny:%secstr%
  return 0
else
  %echoaround% security:allow:%secstr%
end
~
#3102
South: Agency Guard~
2 q 100
~
set vnum %self.vnum%
set secstr %vnum%:%actor.id%:%direction%
%echoaround% security:check:%secstr%
if %direction% == south && %actor.is_pc%
  %send% %actor% Access Denied
  %echoaround% security:deny:%secstr%
  return 0
else
  %echoaround% security:allow:%secstr%
end
~
#3103
West: Agency Guard~
2 q 100
~
set vnum %self.vnum%
set secstr %vnum%:%actor.id%:%direction%
%echoaround% security:check:%secstr%
if %direction% == west && %actor.is_pc%
  %send% %actor% Access Denied
  %echoaround% security:deny:%secstr%
  return 0
else
  %echoaround% security:allow:%secstr%
end
~
#3104
Up: Agency Guard~
2 q 100
~
set vnum %self.vnum%
set secstr %vnum%:%actor.id%:%direction%
%echoaround% security:check:%secstr%
if %direction% == up && %actor.is_pc%
  return 0
  %send% %actor% Access Denied
  %echoaround% security:deny:%secstr%
else
  %echoaround% security:allow:%secstr%
end
~
#3105
Down: Agency Guard~
2 q 100
~
set vnum %self.vnum%
set secstr %vnum%:%actor.id%:%direction%
%echoaround% security:check:%secstr%
if %direction% == down && %actor.is_pc%
  return 0
  %send% %actor% Access Denied
  %echoaround% security:deny:%secstr%
else
  %echoaround% security:allow:%secstr%
end
~
#3106
Security Check~
2 q 100
~
set vnum %self.vnum%
set secstr %vnum%:%actor.id%:%direction%
wait 5 sec
%send% %actor% Security Check
%echoaround% security:check:%secstr%
~
#3107
Security Greeting~
0 g 100
~
say Hello %actor.name%.
~
$~
