@echo off

echo.

set /p SUDO_PASS=Insert Postgres Password:

psql -d template1 -c "ALTER  USER postgres WITH PASSWORD '%SUDO_PASS%'"

echo.
echo.
echo New Postgres Password is: %SUDO_PASS% 
echo.
echo.
pause
