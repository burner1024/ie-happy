READ_LONG  0x2bc "itm_off" ELSE 0
READ_LONG  0x2c0 "itm_num" ELSE 0

PATCH_IF ("itm_off" > 0x2d3) BEGIN
  FOR (index = 0 ; index < itm_num ; index = index + 1) BEGIN
    READ_ASCII ("%itm_off%" + (0x14 * "%index%")) "item"
    PATCH_IF (NOT (FILE_EXISTS_IN_GAME ~%item%.itm~) AND ("%item%" STRING_COMPARE_REGEXP "^[Rr][Nn][Dd].+$")) BEGIN
      converted = 0
      PHP_EACH tutu_convert_itm AS tutu_itm => bgt_itm BEGIN
        PATCH_IF ("%item%" STR_EQ "%tutu_itm%") AND (FILE_EXISTS_IN_GAME "%bgt_itm%.itm") BEGIN
          WRITE_ASCIIE ("%itm_off%" + (0x14 * "%index%")) "%bgt_itm%" #8
          converted = 1
          PATCH_PRINT "HW33: %SOURCE_FILE% - Replacing %tutu_itm%.itm with %bgt_itm%.itm..."
        END
      END
      PATCH_IF ("%converted%" = 0) BEGIN
        PATCH_PRINT "HW34: %SOURCE_FILE% - Inventory Item #%index% (%item%.itm) does not exist! Removing item..."
        REMOVE_CRE_ITEM ~%item%~
        index = (0 - 1)
        READ_LONG  0x2c0 "itm_num"
      END
    END
  END
END
