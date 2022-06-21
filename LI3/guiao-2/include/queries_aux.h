#ifndef QUERIES_AUX_
#define QUERIES_AUX_

#include <time.h>

char *strptime(const char *s, const char *format, struct tm *tm);

int not_future_date(int day, int mon, int year, int day_lmt, int mon_lmt, int year_lmt);

int not_prev_date(int day, int mon, int year, int day_lmt, int mon_lmt, int year_lmt);

void hash_to_list(void *key, void *data, void *traverse_data);

int check_commit_after(GList *list, char *lmt_date);

#endif