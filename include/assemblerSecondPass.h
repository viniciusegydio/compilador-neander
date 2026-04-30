#ifndef ASSEMBLER_SECOND_PASS_H
#define ASSEMBLER_SECOND_PASS_H

int resolve(const char *op);
void secondPass();
void generateMemFile(const char *filename);

#endif