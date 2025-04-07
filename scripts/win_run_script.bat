@echo off
set /a iters=%1
set /a proc_aff=%2
set prog=%~3
set prog_arg=%4

for /l %%i in (1 1 %iters%) do (START /wait /high /b /affinity %proc_aff% %prog% %prog_arg%)
pause
