cls
@echo off
@echo ==============================================================================================================
@echo                                               SEARCH ALGORITHMS
@echo ==============================================================================================================

@echo (1) Breadth_First_Search
@echo (2) Breadth_First_Search_VList
@echo (3) PDS_No_VList
@echo (4) PDS_NonStrict_VList
@echo (5) aStar_ExpList_MisplacedTiles
@echo (6) aStar_ExpList_Manhattan

echo.
set /p selection="Select Algorithm: "
@echo You picked Algorithm # %selection%

echo.
@echo ==============================================================================================================
@echo INIT_STATE (1): 042158367, GOAL_STATE: 123804765
@echo INIT_STATE (2): 364058271, GOAL_STATE: 123804765
@echo INIT_STATE (3): 281463075, GOAL_STATE: 123804765
@echo INIT_STATE (4): 567408321, GOAL_STATE: 123804765
@echo INIT_STATE (5): 4683508721, GOAL_STATE: 123804765
@echo INIT_STATE (6): 471506238, GOAL_STATE: 123804765
@echo INIT_STATE (7): 283104765, GOAL_STATE: 123804765
@echo INIT_STATE (8): 283164705, GOAL_STATE: 123804765
@echo INIT_STATE (9): 845230716, GOAL_STATE: 123804765
@echo INIT_STATE (10): 834215706, GOAL_STATE: 123804765
@echo INIT_STATE (11): 083214765, GOAL_STATE: 123804765
echo.
set /p testcase="Select Test Case: "
@echo You picked Test case # %testcase%

if %selection% == 1 ( set param1= single_run breadth_first_search
  ) else if %selection% == 2 ( set param1= single_run breadth_first_search_vlist
  ) else if %selection% == 3 ( set param1= single_run pds_no_vlist
  ) else if %selection% == 4 ( set param1= single_run pds_nonstrict_vlist
  ) else if %selection% == 5 ( set param1= single_run astar_explist_misplacedtiles
  ) else if %selection% == 6 ( set param1= single_run astar_explist_manhattan )

if %testcase% == 1 ( set param2= 042158367 123804765
  ) else if %testcase% == 2 ( set param2= 364058271 123804765
  ) else if %testcase% == 3 ( set param2= 281463075 123804765
  ) else if %testcase% == 4 ( set param2= 567408321 123804765
  ) else if %testcase% == 5 ( set param2= 463508721 123804765
  ) else if %testcase% == 6 ( set param2= 471506238 123804765
  ) else if %testcase% == 7 ( set param2= 283104765 123804765
  ) else if %testcase% == 8 ( set param2= 283164705 123804765
  ) else if %testcase% == 9 ( set param2= 845230716 123804765
  ) else if %testcase% == 10 ( set param2= 834215706 123804765
  ) else if %testcase% == 11 ( set param2= 083214765 123804765 )

set param=%param1% %param2%
echo %param%
main.exe %param%

@echo ==============================================================================================================
@echo nothing follows.
