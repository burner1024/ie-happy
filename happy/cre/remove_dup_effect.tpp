PATCH_IF (SOURCE_SIZE > 0x2d3) BEGIN
  READ_BYTE  0x33  "eff_ver"
  READ_LONG  0x2a0 "spl_off" ELSE 0
  READ_LONG  0x2a8 "meminfo_off" ELSE 0
  READ_LONG  0x2b0 "mem_off" ELSE 0
  READ_LONG  0x2b8 "slot_off" ELSE 0
  READ_LONG  0x2bc "itm_off" ELSE 0
  READ_LONG  0x2c4 "eff_off" ELSE 0
  READ_LONG  0x2c8 "eff_num" ELSE 0

  PATCH_IF (eff_off > 0x2d3) BEGIN
    PATCH_IF ("%eff_ver%" = 0) BEGIN
      FOR (index = 0 ; index < eff_num ; index = index + 1) BEGIN
        READ_SHORT ("%eff_off%" +        ("%index%" * 0x30)) "opcode"
        READ_BYTE  ("%eff_off%" + 0x02 + ("%index%" * 0x30)) "target"
        READ_BYTE  ("%eff_off%" + 0x03 + ("%index%" * 0x30)) "power"
        READ_LONG  ("%eff_off%" + 0x04 + ("%index%" * 0x30)) "param1"
        READ_LONG  ("%eff_off%" + 0x08 + ("%index%" * 0x30)) "param2"
        READ_BYTE  ("%eff_off%" + 0x0c + ("%index%" * 0x30)) "timing"
        READ_BYTE  ("%eff_off%" + 0x0d + ("%index%" * 0x30)) "dispel"
        READ_LONG  ("%eff_off%" + 0x0e + ("%index%" * 0x30)) "duration"
        READ_BYTE  ("%eff_off%" + 0x12 + ("%index%" * 0x30)) "prob1"
        READ_BYTE  ("%eff_off%" + 0x13 + ("%index%" * 0x30)) "prob2"
        READ_ASCII ("%eff_off%" + 0x14 + ("%index%" * 0x30)) "resref"
        READ_LONG  ("%eff_off%" + 0x1c + ("%index%" * 0x30)) "diccnt"
        READ_LONG  ("%eff_off%" + 0x20 + ("%index%" * 0x30)) "dicsid"
        READ_LONG  ("%eff_off%" + 0x24 + ("%index%" * 0x30)) "savtyp"
        READ_LONG  ("%eff_off%" + 0x28 + ("%index%" * 0x30)) "savbon"
        FOR (index1 = 0 ; index1 < eff_num ; index1 = index1 + 1) BEGIN
          PATCH_IF ("%index1%" != "%index%") BEGIN
            READ_SHORT ("%eff_off%" +        ("%index1%" * 0x30)) "eff_opcode"
            READ_BYTE  ("%eff_off%" + 0x02 + ("%index1%" * 0x30)) "eff_target"
            READ_BYTE  ("%eff_off%" + 0x03 + ("%index1%" * 0x30)) "eff_power"
            READ_LONG  ("%eff_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
            READ_LONG  ("%eff_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
            READ_BYTE  ("%eff_off%" + 0x0c + ("%index1%" * 0x30)) "eff_timing"
            READ_BYTE  ("%eff_off%" + 0x0d + ("%index1%" * 0x30)) "eff_dispel"
            READ_LONG  ("%eff_off%" + 0x0e + ("%index1%" * 0x30)) "eff_duration"
            READ_BYTE  ("%eff_off%" + 0x12 + ("%index1%" * 0x30)) "eff_prob1"
            READ_BYTE  ("%eff_off%" + 0x13 + ("%index1%" * 0x30)) "eff_prob2"
            READ_ASCII ("%eff_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
            READ_LONG  ("%eff_off%" + 0x1c + ("%index1%" * 0x30)) "eff_diccnt"
            READ_LONG  ("%eff_off%" + 0x20 + ("%index1%" * 0x30)) "eff_dicsid"
            READ_LONG  ("%eff_off%" + 0x24 + ("%index1%" * 0x30)) "eff_savtyp"
            READ_LONG  ("%eff_off%" + 0x28 + ("%index1%" * 0x30)) "eff_savbon"
            PATCH_IF ("%opcode%" = "%eff_opcode%") AND
                      ("%target%" = "%eff_target%") AND
                      ("%power%" = "%eff_power%") AND
                      ("%param1%" = "%eff_param1%") AND
                      ("%param2%" = "%eff_param2%") AND
                      ("%timing%" = "%eff_timing%") AND
                      ("%dispel%" = "%eff_dispel%") AND
                      ("%duration%" = "%eff_duration%") AND
                      ("%prob1%" = "%eff_prob1%") AND
                      ("%prob2%" = "%eff_prob2%") AND
                      ("%resref%" STR_EQ "%eff_resref%") AND
                      ("%diccnt%" = "%eff_diccnt%") AND
                      ("%dicsid%" = "%eff_dicsid%") AND
                      ("%savtyp%" = "%eff_savtyp%") AND
                      ("%savbon%" = "%eff_savbon%") BEGIN
              PATCH_PRINT "HI25: %SOURCE_FILE% - Effect #%index1% (Opcode %opcode%) matches Effect #%index%! Removing..."
              offset = "%eff_off%" + ("%index1%" * 0x30)
              value  = 0x30
              DELETE_BYTES offset value
              SOURCE_SIZE = SOURCE_SIZE - value
              SET "index1" = 0 - 1
              SET "eff_num" = "eff_num" - 1
              WRITE_LONG 0x2c8 %eff_num%
              PATCH_IF ("%spl_off%" > "%eff_off%") BEGIN
                SET "spl_off" = "spl_off" - 0x30
                WRITE_LONG 0x2a0 %spl_off%
              END
              PATCH_IF ("%meminfo_off%" > "%eff_off%") BEGIN
                SET "meminfo_off" = "meminfo_off" - 0x30
                WRITE_LONG 0x2a8 %meminfo_off%
              END
              PATCH_IF ("%mem_off%" > "%eff_off%") BEGIN
                SET "mem_off" = "mem_off" - 0x30
                WRITE_LONG 0x2b0 %mem_off%
              END
              PATCH_IF ("%slot_off%" > "%eff_off%") BEGIN
                SET "slot_off" = "slot_off" - 0x30
                WRITE_LONG 0x2b8 %slot_off%
              END
              PATCH_IF ("%itm_off%" > "%eff_off%") BEGIN
                SET "itm_off" = "itm_off" - 0x30
                WRITE_LONG 0x2bc %itm_off%
              END
            END
          END
        END
      END
    END ELSE PATCH_IF ("%eff_ver%" = 1) BEGIN
      FOR (index = 0 ; index < eff_num ; index = index + 1) BEGIN
        READ_LONG  ("%eff_off%" + 0x08 + ("%index%" * 0x108)) "opcode"
        READ_LONG  ("%eff_off%" + 0x0c + ("%index%" * 0x108)) "target"
        READ_LONG  ("%eff_off%" + 0x10 + ("%index%" * 0x108)) "power"
        READ_LONG  ("%eff_off%" + 0x14 + ("%index%" * 0x108)) "param1"
        READ_LONG  ("%eff_off%" + 0x18 + ("%index%" * 0x108)) "param2"
        READ_SHORT ("%eff_off%" + 0x1c + ("%index%" * 0x108)) "timing"
        READ_LONG  ("%eff_off%" + 0x20 + ("%index%" * 0x108)) "duration"
        READ_SHORT ("%eff_off%" + 0x24 + ("%index%" * 0x108)) "prob1"
        READ_SHORT ("%eff_off%" + 0x26 + ("%index%" * 0x108)) "prob2"
        READ_ASCII ("%eff_off%" + 0x28 + ("%index%" * 0x108)) "resref"
        READ_LONG  ("%eff_off%" + 0x30 + ("%index%" * 0x108)) "diccnt"
        READ_LONG  ("%eff_off%" + 0x34 + ("%index%" * 0x108)) "dicsid"
        READ_LONG  ("%eff_off%" + 0x38 + ("%index%" * 0x108)) "savtyp"
        READ_LONG  ("%eff_off%" + 0x3c + ("%index%" * 0x108)) "savbon"
        READ_LONG  ("%eff_off%" + 0x54 + ("%index%" * 0x108)) "dispel"
        FOR (index1 = 0 ; index1 < eff_num ; index1 = index1 + 1) BEGIN
          PATCH_IF ("%index1%" != "%index%") BEGIN
            READ_LONG  ("%eff_off%" + 0x08 + ("%index1%" * 0x108)) "eff_opcode"
            READ_LONG  ("%eff_off%" + 0x0c + ("%index1%" * 0x108)) "eff_target"
            READ_LONG  ("%eff_off%" + 0x10 + ("%index1%" * 0x108)) "eff_power"
            READ_LONG  ("%eff_off%" + 0x14 + ("%index1%" * 0x108)) "eff_param1"
            READ_LONG  ("%eff_off%" + 0x18 + ("%index1%" * 0x108)) "eff_param2"
            READ_SHORT ("%eff_off%" + 0x1c + ("%index1%" * 0x108)) "eff_timing"
            READ_LONG  ("%eff_off%" + 0x20 + ("%index1%" * 0x108)) "eff_duration"
            READ_SHORT ("%eff_off%" + 0x24 + ("%index1%" * 0x108)) "eff_prob1"
            READ_SHORT ("%eff_off%" + 0x26 + ("%index1%" * 0x108)) "eff_prob2"
            READ_ASCII ("%eff_off%" + 0x28 + ("%index1%" * 0x108)) "eff_resref"
            READ_LONG  ("%eff_off%" + 0x30 + ("%index1%" * 0x108)) "eff_diccnt"
            READ_LONG  ("%eff_off%" + 0x34 + ("%index1%" * 0x108)) "eff_dicsid"
            READ_LONG  ("%eff_off%" + 0x38 + ("%index1%" * 0x108)) "eff_savtyp"
            READ_LONG  ("%eff_off%" + 0x3c + ("%index1%" * 0x108)) "eff_savbon"
            READ_LONG  ("%eff_off%" + 0x54 + ("%index1%" * 0x108)) "eff_dispel"
            PATCH_IF ("%opcode%" = "%eff_opcode%") AND
                      ("%target%" = "%eff_target%") AND
                      ("%power%" = "%eff_power%") AND
                      ("%param1%" = "%eff_param1%") AND
                      ("%param2%" = "%eff_param2%") AND
                      ("%timing%" = "%eff_timing%") AND
                      ("%dispel%" = "%eff_dispel%") AND
                      ("%duration%" = "%eff_duration%") AND
                      ("%prob1%" = "%eff_prob1%") AND
                      ("%prob2%" = "%eff_prob2%") AND
                      ("%resref%" STR_EQ "%eff_resref%") AND
                      ("%diccnt%" = "%eff_diccnt%") AND
                      ("%dicsid%" = "%eff_dicsid%") AND
                      ("%savtyp%" = "%eff_savtyp%") AND
                      ("%savbon%" = "%eff_savbon%") BEGIN
              PATCH_PRINT "HI26: %SOURCE_FILE% - Effect #%index1% (Opcode %opcode%) matches Effect #%index%! Removing..."
              offset = "%eff_off%" + ("%index1%" * 0x108)
              value  = 0x108
              DELETE_BYTES offset value
              SOURCE_SIZE = SOURCE_SIZE - value
              SET "index1" = 0 - 1
              SET "eff_num" = "eff_num" - 1
              WRITE_LONG 0x2c8 %eff_num%
              PATCH_IF ("%spl_off%" > "%eff_off%") BEGIN
                SET "spl_off" = "spl_off" - 0x108
                WRITE_LONG 0x2a0 %spl_off%
              END
              PATCH_IF ("%meminfo_off%" > "%eff_off%") BEGIN
                SET "meminfo_off" = "meminfo_off" - 0x108
                WRITE_LONG 0x2a8 %meminfo_off%
              END
              PATCH_IF ("%mem_off%" > "%eff_off%") BEGIN
                SET "mem_off" = "mem_off" - 0x108
                WRITE_LONG 0x2b0 %mem_off%
              END
              PATCH_IF ("%slot_off%" > "%eff_off%") BEGIN
                SET "slot_off" = "slot_off" - 0x108
                WRITE_LONG 0x2b8 %slot_off%
              END
              PATCH_IF ("%itm_off%" > "%eff_off%") BEGIN
                SET "itm_off" = "itm_off" - 0x108
                WRITE_LONG 0x2bc %itm_off%
              END
            END
          END
        END
      END
    END
  END
END
