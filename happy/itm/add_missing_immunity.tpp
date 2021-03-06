READ_BYTE  0x18 "flags"

PATCH_IF (("%flags%" BAND 0b00000100) = 0b00000100) BEGIN  // droppable

  // Equipped Effect Fixer
  READ_LONG  0x6a "fx_off" ELSE 0
  READ_SHORT 0x6e "fx_idx" ELSE 0
  READ_SHORT 0x70 "fx_num" ELSE 0

  PATCH_IF (fx_off > 0x71) BEGIN
    FOR (index = fx_idx ; index < fx_num ; index = index + 1) BEGIN // check equipping effects
      READ_SHORT ("%fx_off%" +        ("%index%" * 0x30)) "opcode"
      READ_LONG  ("%fx_off%" + 0x04 + ("%index%" * 0x30)) "param1"
      READ_LONG  ("%fx_off%" + 0x08 + ("%index%" * 0x30)) "param2"
      READ_ASCII ("%fx_off%" + 0x14 + ("%index%" * 0x30)) "resref"

      // Charm
      PATCH_IF (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPPR204")) OR
                (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPPR405")) OR
                (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPWI104")) OR
                (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPWI316")) OR
                (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPWI506")) OR
                (("%opcode%" = 101) AND ("%param2%" = 5)) BEGIN
        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 5) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW134: %SOURCE_FILE% - Adding Immunity to Charm..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 5
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 52) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW135: %SOURCE_FILE% - Adding Mind Shield Portrait..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 142
              target     = 1
              timing     = 2
              parameter2 = 52
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 0) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW136: %SOURCE_FILE% - Preventing Charm Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 0
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 1) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW137: %SOURCE_FILE% - Preventing Dire Charm Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 1
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 43) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW138: %SOURCE_FILE% - Preventing Domination Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 43
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 8364) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW139: %SOURCE_FILE% - Disabling 'Dominated' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 8364
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 14672) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW140: %SOURCE_FILE% - Disabling 'Charmed' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 14672
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 14780) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW141: %SOURCE_FILE% - Disabling 'Dire Charmed' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 14780
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_ASCII ("%fx_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
          PATCH_IF ("%eff_opcode%" = 296) AND ("%eff_resref%" STR_EQ "spnwchrm") BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW142: %SOURCE_FILE% - Preventing Charm Animation..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 296
              target     = 1
              timing     = 2
            STR_VAR
              resource   = "spnwchrm"
          END
          READ_SHORT 0x70 "fx_num"
        END
      END

      // Hold
      PATCH_IF (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPPR208")) OR
                (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPWI306")) OR
                (("%opcode%" = 101) AND ("%param2%" = 109)) OR
                (("%opcode%" = 101) AND ("%param2%" = 175)) OR
                (("%opcode%" = 101) AND ("%param2%" = 185)) BEGIN
        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 109) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW143: %SOURCE_FILE% - Adding Immunity to Hold..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 109
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 175) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW144: %SOURCE_FILE% - Adding Immunity to Hold Creature Type 1..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 175
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 185) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW145: %SOURCE_FILE% - Adding Immunity to Hold Creature Type 2..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 185
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 13) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW146: %SOURCE_FILE% - Preventing Held Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 13
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 14102) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW147: %SOURCE_FILE% - Disabling 'Held' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 14102
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_ASCII ("%fx_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
          PATCH_IF ("%eff_opcode%" = 296) AND ("%eff_resref%" STR_EQ "spmindat") BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW148: %SOURCE_FILE% - Preventing Hold Animation 1..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 296
              target     = 1
              timing     = 2
            STR_VAR
              resource   = "spmindat"
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_ASCII ("%fx_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
          PATCH_IF ("%eff_opcode%" = 296) AND ("%eff_resref%" STR_EQ "spflayer") BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW149: %SOURCE_FILE% - Preventing Hold Animation 2..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 296
              target     = 1
              timing     = 2
            STR_VAR
              resource   = "spflayer"
          END
          READ_SHORT 0x70 "fx_num"
        END
      END

      // Confusion
      PATCH_IF (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPPR709")) OR
                (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPWI401")) OR
                (("%opcode%" = 101) AND ("%param2%" = 128)) BEGIN
        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 128) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW150: %SOURCE_FILE% - Adding Immunity to Confusion..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 128
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 2) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW151: %SOURCE_FILE% - Preventing Rigid Thinking Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 2
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 3) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW152: %SOURCE_FILE% - Preventing Confused Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 3
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 47) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW153: %SOURCE_FILE% - Preventing Chaos Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 47
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 14782) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW154: %SOURCE_FILE% - Disabling 'Confused' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 14782
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 14791) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW155: %SOURCE_FILE% - Disabling 'Rigid Thinking' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 14791
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_ASCII ("%fx_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
          PATCH_IF ("%eff_opcode%" = 296) AND ("%eff_resref%" STR_EQ "spconfus") BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW156: %SOURCE_FILE% - Preventing Confusion Animation..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 296
              target     = 1
              timing     = 2
            STR_VAR
              resource   = "spconfus"
          END
          READ_SHORT 0x70 "fx_num"
        END
      END

      // Feeblemind
      PATCH_IF (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPWI509")) OR
                (("%opcode%" = 101) AND ("%param2%" = 76)) BEGIN
        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 76) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW157: %SOURCE_FILE% - Adding Immunity to Feeblemindedness..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 76
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 48) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW158: %SOURCE_FILE% - Preventing Feebleminded Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 48
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_ASCII ("%fx_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
          PATCH_IF ("%eff_opcode%" = 296) AND ("%eff_resref%" STR_EQ "spmindat") BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW159: %SOURCE_FILE% - Preventing Feebleminded Animation..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 296
              target     = 1
              timing     = 2
            STR_VAR
              resource   = "spmindat"
          END
          READ_SHORT 0x70 "fx_num"
        END
      END

      // Horror
      PATCH_IF (("%opcode%" = 206) AND ("%resref%" STR_EQ "SPWI205")) OR
                (("%opcode%" = 101) AND ("%param2%" = 23)) OR
                (("%opcode%" = 101) AND ("%param2%" = 24)) OR
                (("%opcode%" = 101) AND ("%param2%" = 106)) BEGIN
        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          PATCH_IF ("%eff_opcode%" = 23) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW160: %SOURCE_FILE% - Adding effect to Reset Morale..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 23
              target     = 1
              timing     = 2
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 23) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW161: %SOURCE_FILE% - Adding Immunity to Morale Reset..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 23
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 24) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW162: %SOURCE_FILE% - Adding Immunity to Panic..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 24
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 101) AND ("%eff_param2%" = 106) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW163: %SOURCE_FILE% - Adding Immunity to Morale Break..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 101
              target     = 1
              timing     = 2
              parameter2 = 106
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 142) AND ("%eff_param2%" = 37) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW164: %SOURCE_FILE% - Adding Resist Fear Portrait..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 142
              target     = 1
              timing     = 2
              parameter2 = 37
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          PATCH_IF ("%eff_opcode%" = 161) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW165: %SOURCE_FILE% - Adding effect to Remove Fear..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 161
              target     = 1
              timing     = 2
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 169) AND ("%eff_param2%" = 36) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW166: %SOURCE_FILE% - Preventing Panic Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 169
              target     = 1
              timing     = 2
              parameter2 = 36
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x08 + ("%index1%" * 0x30)) "eff_param2"
          PATCH_IF ("%eff_opcode%" = 240) AND ("%eff_param2%" = 36) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW167: %SOURCE_FILE% - Adding effect to Remove Panic Icon..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 240
              target     = 1
              timing     = 2
              parameter2 = 36
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 14007) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW168: %SOURCE_FILE% - Disabling 'Panic' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 14007
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 17427) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW169: %SOURCE_FILE% - Disabling 'Panic' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 17427
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 267) AND ("%eff_param1%" = 20568) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW170: %SOURCE_FILE% - Disabling 'Morale Failure: Panic' String..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 267
              target     = 1
              timing     = 2
              parameter1 = 20568
          END
          READ_SHORT 0x70 "fx_num"
        END

        SET "found" = 0
        FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
          READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
          READ_LONG  ("%fx_off%" + 0x04 + ("%index1%" * 0x30)) "eff_param1"
          PATCH_IF ("%eff_opcode%" = 106) AND ("%eff_param1%" = 1) BEGIN
            SET "found" = 1
          END
        END
        PATCH_IF ("%found%" = 0) BEGIN
          PATCH_PRINT "HW171: %SOURCE_FILE% - Preventing morale failure..."
          LPF ADD_ITEM_EQEFFECT
            INT_VAR
              opcode     = 106
              target     = 1
              timing     = 2
              parameter1 = 1
              parameter2 = 1
          END
          READ_SHORT 0x70 "fx_num"
        END

        PATCH_IF FILE_EXISTS_IN_GAME ~cdhorror.vvc~ BEGIN
          SET "found" = 0
          FOR (index1 = fx_idx ; index1 < fx_num ; index1 = index1 + 1) BEGIN // check equipping effects
            READ_SHORT ("%fx_off%" +        ("%index1%" * 0x30)) "eff_opcode"
            READ_ASCII ("%fx_off%" + 0x14 + ("%index1%" * 0x30)) "eff_resref"
            PATCH_IF ("%eff_opcode%" = 296) AND ("%eff_resref%" STR_EQ "cdhorror") BEGIN
              SET "found" = 1
            END
          END
          PATCH_IF ("%found%" = 0) BEGIN
            PATCH_PRINT "HW172: %SOURCE_FILE% - Preventing BG2Fixpack confusion Animation..."
            LPF ADD_ITEM_EQEFFECT
              INT_VAR
                opcode     = 296
                target     = 1
                timing     = 2
              STR_VAR
                resource   = "cdhorror"
            END
            READ_SHORT 0x70 "fx_num"
          END
        END
      END

    END
  END
END
