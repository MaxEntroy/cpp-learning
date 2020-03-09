#ifndef TASK_H_
#define TASK_H_

#include "proto/cal_req.pb.h"
#include "proto/cal_res.pb.h"

void DoRequest(cal::Request* req, int left, int right);
void DoTask(const cal::Request& req, cal::Response* res);
void DoResponse(const cal::Response& res);

#endif
