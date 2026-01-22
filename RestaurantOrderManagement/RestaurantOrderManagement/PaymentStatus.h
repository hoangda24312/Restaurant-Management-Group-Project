#pragma once
#include "common.h"
enum class PaymentStatus
{
    PENDING,
    PAID,
    REFUNDED
};


std::string paymentStatusToString(PaymentStatus status);