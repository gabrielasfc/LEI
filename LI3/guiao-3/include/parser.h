#ifndef PARSER_
#define PARSER_

#include "cat_commits.h"
#include "cat_repos.h"
#include "cat_users.h"

char *strptime(const char *s, const char *format, struct tm *tm);

void** data_to_catalogues_with_parsing(Cat_Users cat_users, Cat_Commits cat_commits, Cat_Repos cat_repos);

#endif