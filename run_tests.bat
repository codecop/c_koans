@rem Run all tests of all sessions.
@cls
@color 02
call make all
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

bin\about_basics
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

bin\about_arrays
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

bin\about_control_statements
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem needs sizeof
bin\about_strings
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem needs arrays, sizeof
bin\about_dataclasses
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem needs string
bin\about_functions
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

bin\about_io
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem needs string, arrays
bin\about_pointers
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem needs strings, pointers
bin\about_malloc
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem needs string
bin\about_preprocessor
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem needs string
bin\about_printing
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

bin\about_structs
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

@rem an application of pointers and structs
bin\about_linked_lists
@if errorlevel 1 @color 04 && @echo FAILED && @goto end

:end
@pause
run_tests.bat
