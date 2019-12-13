INCLUDE ~%MOD_FOLDER%/lib/functions.tpa~

// Delete Magic fire/cold damage and protection
ACTION_DEFINE_ASSOCIATIVE_ARRAY dtype BEGIN
  33554432   =>  ~Magical Fire~
  33554433   =>  ~Magical Fire Set to Value~
  33554434   =>  ~Magical Fire Set to Percentage~
  33554435   =>  ~Magical Fire (Max HP Percentage)~
  67108864   =>  ~Magical Cold~
  67108865   =>  ~Magical Cold Set to Value~
  67108866   =>  ~Magical Cold Set to Value~
  67108867   =>  ~Magical Cold (Max HP Percentage)~
  134217728  =>  ~Stunning~
  134217729  =>  ~Stunning Set to Value~
  134217730  =>  ~Stunning Set to Percentage~
  134217731  =>  ~Stunning (Max HP Percentage)~
END

ACTION_DEFINE_ASSOCIATIVE_ARRAY rtype BEGIN
  84 => ~Magical Fire~
  85 => ~Magical Cold~
END

COPY_EXISTING_REGEXP GLOB ~^.+\.itm$~ ~override~
  GET_OFFSET_ARRAY fx_array ITM_V10_GEN_EFFECTS
  PHP_EACH fx_array AS int => fx_off BEGIN size=int END //ugly hack to count array size
    PHP_EACH fx_array AS int => fx_off BEGIN
      PATCH_IF int <= size BEGIN
      READ_SHORT fx_off opcode
      READ_LONG (fx_off+0x8) parameter2
      PATCH_IF (opcode = 12 AND (VARIABLE_IS_SET $dtype(~%parameter2%~))) BEGIN
        SPRINT dtype_string $dtype(~%parameter2%~)
        PATCH_PRINT ~HE8: %SOURCE_FILE% - damage of type %dtype_string%. Removing.~
        LPF G_DELETE_ITEM_EFFECT  INT_VAR opcode = %opcode% check_globals = 1 parameter2 = %parameter2%  END
      END
      PATCH_IF (VARIABLE_IS_SET $rtype(~%opcode%~)) BEGIN
        SPRINT rtype_string $rtype(~%opcode%~)
        PATCH_PRINT ~HI63: %SOURCE_FILE% - an effect adds resistance to nonexistent damage type %rtype_string%. Removing.~
        LPF G_DELETE_ITEM_EFFECT  INT_VAR opcode = %opcode% check_globals = 1  END
        size -= 1
      END
    END
  END
BUT_ONLY



ACTION_DEFINE_ASSOCIATIVE_ARRAY opcode_with_res BEGIN
  67  => ~cre~
  135 => ~cre~
  151 => ~cre~
  168 => ~cre~

  111 => ~itm~
  112 => ~itm~
  122 => ~itm~
  143 => ~itm~

  146 => ~spl~
  147 => ~spl~
  148 => ~spl~
  171 => ~spl~
  172 => ~spl~
  206 => ~spl~
  207 => ~spl~
  232 => ~spl~
  266 => ~spl~

  152 => ~mve~

  174 => ~wav~

  107 => ~bmp~

  177 => ~eff~
  248 => ~eff~
  249 => ~eff~

  186 => ~are~
END

COPY_EXISTING_REGEXP GLOB ~^.+\.itm$~ ~override~
  CLEAR_ARRAY fx_array
  CLEAR_ARRAY delete_opcode
  CLEAR_ARRAY delete_resref
  GET_OFFSET_ARRAY fx_array ITM_V10_GEN_EFFECTS
  i = 0

  PHP_EACH fx_array AS int => fx_off BEGIN
    READ_SHORT fx_off opcode
    READ_ASCII (fx_off+0x14) resref
    PATCH_IF VARIABLE_IS_SET $opcode_with_res(~%opcode%~) BEGIN
      SPRINT ext $opcode_with_res(~%opcode%~)
      PATCH_IF NOT FILE_EXISTS_IN_GAME ~%resref%.%ext%~ BEGIN
        PATCH_PRINT ~HW232: %SOURCE_FILE% - effect with opcode %opcode% refers to a non-existent resource %resref%.%ext%. Removing.~
        SET $delete_opcode(~%i%~) = opcode
        SPRINT $delete_resref(~%i%~) ~%resref%~
        i = i + 1
      END
    END
  END

  PHP_EACH delete_opcode AS i2 => opcode BEGIN
    SPRINT resref $delete_resref(~%i2%~)
    LPF G_DELETE_ITEM_EFFECT
      INT_VAR opcode = %opcode%  check_globals = 1
      STR_VAR resource = EVAL ~%resref%~
    END
  END

BUT_ONLY
