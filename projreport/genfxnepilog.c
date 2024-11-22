void GenFxnEpilog(void) {
  GenUpdateFrameSize();
  // Check if the function called another function
  if (!GenLeaf) {
    // Load Canary from Stack into temp register 1
    GenPrintInstr2Operands(
      MipsInstrLW, 0,
      MipsOpRegT1, 0,
      MipsOpRegFp, 12
    );
    // Load Canary from Storage Location into temp register 2
    GenPrintInstr2Operands(
      MipsInstrLW, 0,
      MipsOpRegT2, 0,
      CanaryStorageLocation, 0
    );
    // Compare the two values, if they aren't equal, crash.
    GenPrintInstr3Operands(
      MipsInstrBNE, 0,
      MipsOpRegT1, 0,
      MipsOpRegT2, 0,
      MipsInstrExit, 0
    );
    // Load the return address we stored on the stack into the return address register
    GenPrintInstr2Operands(
      MipsInstrLW, 0,
      MipsOpRegRa, 0,
      MipsOpIndRegFp, 4
    );
  }
  // Load the previous frame pointer back into a register
  GenPrintInstr2Operands(
    MipsInstrLW, 0,
    MipsOpRegFp, 0,
    MipsOpIndRegFp, 0
  );
  // Move the stack pointer past the function frame
  GenPrintInstr3Operands(
    MipsInstrAddU, 0,
    MipsOpRegSp, 0,
    MipsOpRegSp, 0,
    MipsOpConst, 12 - CurFxnMinLocalOfs
  );  //12 = RA + FP + Canary
  // Jump to the return address and continue execution
  GenPrintInstr1Operand(
    MipsInstrJ, 0,
    MipsOpRegRa, 0
  );
}
