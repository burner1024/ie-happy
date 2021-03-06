// Container Content Validator
READ_LONG  0x70 "cont_off" ELSE 0
READ_SHORT 0x74 "cont_num" ELSE 0

PATCH_IF (cont_off > 0x11b) BEGIN
  FOR (index = 0 ; index < cont_num ; index = index + 1) BEGIN
    cur_off = cont_off + 0xc0 * index
    READ_SHORT (cur_off + 0x30) trapped
    READ_SHORT (cur_off + 0x2c) detection_diff
    READ_SHORT (cur_off + 0x2e) removal_diff
    READ_SHORT (cur_off + 0x32) detected
    READ_ASCII (cur_off + 0x48) script
    READ_LONG (cur_off + 0x28) flags
    locked = flags BAND 0b1
    READ_SHORT (cur_off + 0x26) lock_diff

    PATCH_IF (trapped == 1 AND NOT FILE_EXISTS_IN_GAME ~%script%.bcs~) BEGIN
      PATCH_PRINT ~HW1: Container #%index% is marked as trapped but trap script %script% does not exist! Clearing trapped flag...~
      WRITE_SHORT (cur_off + 0x30) 0
      WRITE_SHORT (cur_off + 0x2c) 0
      WRITE_SHORT (cur_off + 0x2e) 0
      WRITE_SHORT (cur_off + 0x32) 0
      WRITE_ASCII (cur_off + 0x48) ~~ #8
    END

    PATCH_IF trapped == 0 BEGIN
      PATCH_IF detection_diff != 0 BEGIN
        PATCH_PRINT ~HI4: Container #%index% is not marked as trapped but trap detection difficulty is set to %detection_diff%! Resetting to 0...~
        WRITE_SHORT (cur_off + 0x2c) 0
      END
      PATCH_IF removal_diff != 0 BEGIN
        PATCH_PRINT ~HI5: Container #%index% is not marked as trapped but trap removal difficulty is set to %removal_diff%! Resetting to 0...~
        WRITE_SHORT (cur_off + 0x2e) 0
      END
      PATCH_IF detected != 0 BEGIN
        PATCH_PRINT ~HI6: Container #%index% is not marked as trapped but trap detected flag is set to %detected%! Resetting to 0...~
        WRITE_SHORT (cur_off + 0x32) 0
      END
    END

    PATCH_IF locked == 0 AND lock_diff > 0 BEGIN
      PATCH_PRINT ~HI7: Container #%index% is not marked as locked but lock difficulty is set to %lock_diff%! Resetting to 0...~
      WRITE_SHORT (cur_off + 0x26) 0
    END

  END
END
