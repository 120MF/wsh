#ifndef INCLUDE_SRC_LOOP_H_
#define INCLUDE_SRC_LOOP_H_

#include "parser.h"

void loop();
void child_process(ParseResult::Process &pro);
void apply_pipe(ParseResult::Process &pro);
void apply_redirect(ParseResult::Process &pro);

#endif // INCLUDE_SRC_LOOP_H_
