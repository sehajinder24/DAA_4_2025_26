@echo off
echo Starting Maze Solver...

REM Start Flask backend
start cmd /k python server.py

REM Wait a bit so Flask starts
timeout /t 2 > nul

REM Start frontend server
start cmd /k python -m http.server 5500

REM Wait again
timeout /t 2 > nul

REM Open browser
start http://localhost:5500

echo Done!