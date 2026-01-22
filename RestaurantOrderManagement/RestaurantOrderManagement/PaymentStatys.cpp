#include "PaymentStatus.h"

std::string paymentStatusToString(PaymentStatus status) {
    switch (status) {
    case PaymentStatus::PAID: return "PAID";
    case PaymentStatus::REFUNDED: return "REFUNDED";
    default: return "PENDING";
    }
}