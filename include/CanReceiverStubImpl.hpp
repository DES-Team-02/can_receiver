#ifndef CANRECEIVERSTUBIMPL_HPP
#define CANRECEIVERSTUBIMPL_HPP

#include <CommonAPI/CommonAPI.hpp>
#include <v0/commonapi/CanReceiverStubDefault.hpp>

class CanReceiverStubImpl: public v0_1::commonapi::CanReceiverStubDefault
{
public:
    CanReceiverStubImpl();
    virtual ~CanReceiverStubImpl();
};

#endif // CANRECEIVERSTUBIMPL_HPP
