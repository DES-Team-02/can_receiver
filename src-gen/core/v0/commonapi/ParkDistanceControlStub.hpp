/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.core 3.2.14.v202310241605.
* Used org.franca.core 0.13.1.201807231814.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V0_COMMONAPI_Park_Distance_Control_STUB_HPP_
#define V0_COMMONAPI_Park_Distance_Control_STUB_HPP_

#include <functional>
#include <sstream>




#include <v0/commonapi/ParkDistanceControl.hpp>

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#define HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

#include <CommonAPI/Deployment.hpp>
#include <CommonAPI/InputStream.hpp>
#include <CommonAPI/OutputStream.hpp>
#include <CommonAPI/Struct.hpp>
#include <cstdint>

#include <mutex>

#include <CommonAPI/Stub.hpp>

#if defined (HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE)
#undef COMMONAPI_INTERNAL_COMPILATION
#undef HAS_DEFINED_COMMONAPI_INTERNAL_COMPILATION_HERE
#endif

namespace v0 {
namespace commonapi {

/**
 * Receives messages from remote and handles all dispatching of deserialized calls
 * to a stub for the service ParkDistanceControl. Also provides means to send broadcasts
 * and attribute-changed-notifications of observable attributes as defined by this service.
 * An application developer should not need to bother with this class.
 */
class ParkDistanceControlStubAdapter
    : public virtual CommonAPI::StubAdapter,
      public virtual ParkDistanceControl {
 public:
    ///Notifies all remote listeners about a change of value of the attribute distances.
    virtual void fireDistancesAttributeChanged(const ::v0::commonapi::ParkDistanceControl::SonarArrayStruct &distances) = 0;


    virtual void deactivateManagedInstances() = 0;

    void lockDistancesAttribute(bool _lockAccess) {
        if (_lockAccess) {
            distancesMutex_.lock();
        } else {
            distancesMutex_.unlock();
        }
    }

protected:
    /**
     * Defines properties for storing the ClientIds of clients / proxies that have
     * subscribed to the selective broadcasts
     */
    std::recursive_mutex distancesMutex_;

};

/**
 * Defines the necessary callbacks to handle remote set events related to the attributes
 * defined in the IDL description for ParkDistanceControl.
 * For each attribute two callbacks are defined:
 * - a verification callback that allows to verify the requested value and to prevent setting
 *   e.g. an invalid value ("onRemoteSet<AttributeName>").
 * - an action callback to do local work after the attribute value has been changed
 *   ("onRemote<AttributeName>Changed").
 *
 * This class and the one below are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class ParkDistanceControlStubRemoteEvent
{
public:
    virtual ~ParkDistanceControlStubRemoteEvent() { }

};

/**
 * Defines the interface that must be implemented by any class that should provide
 * the service ParkDistanceControl to remote clients.
 * This class and the one above are the ones an application developer needs to have
 * a look at if he wants to implement a service.
 */
class ParkDistanceControlStub
    : public virtual CommonAPI::Stub<ParkDistanceControlStubAdapter, ParkDistanceControlStubRemoteEvent>
{
public:

    virtual ~ParkDistanceControlStub() {}
    void lockInterfaceVersionAttribute(bool _lockAccess) { static_cast<void>(_lockAccess); }
    bool hasElement(const uint32_t _id) const {
        return (_id < 1);
    }
    virtual const CommonAPI::Version& getInterfaceVersion(std::shared_ptr<CommonAPI::ClientId> _client) = 0;

    /// Provides getter access to the attribute distances
    virtual const ::v0::commonapi::ParkDistanceControl::SonarArrayStruct &getDistancesAttribute(const std::shared_ptr<CommonAPI::ClientId> _client) = 0;
    /// sets attribute with the given value and propagates it to the adapter
    virtual void fireDistancesAttributeChanged(::v0::commonapi::ParkDistanceControl::SonarArrayStruct _value) {
    auto stubAdapter = CommonAPI::Stub<ParkDistanceControlStubAdapter, ParkDistanceControlStubRemoteEvent>::stubAdapter_.lock();
    if (stubAdapter)
        stubAdapter->fireDistancesAttributeChanged(_value);
    }
    void lockDistancesAttribute(bool _lockAccess) {
        auto stubAdapter = CommonAPI::Stub<ParkDistanceControlStubAdapter, ParkDistanceControlStubRemoteEvent>::stubAdapter_.lock();
        if (stubAdapter)
            stubAdapter->lockDistancesAttribute(_lockAccess);
    }


    using CommonAPI::Stub<ParkDistanceControlStubAdapter, ParkDistanceControlStubRemoteEvent>::initStubAdapter;
    typedef CommonAPI::Stub<ParkDistanceControlStubAdapter, ParkDistanceControlStubRemoteEvent>::StubAdapterType StubAdapterType;
    typedef CommonAPI::Stub<ParkDistanceControlStubAdapter, ParkDistanceControlStubRemoteEvent>::RemoteEventHandlerType RemoteEventHandlerType;
    typedef ParkDistanceControlStubRemoteEvent RemoteEventType;
    typedef ::v0::commonapi::ParkDistanceControl StubInterface;
};

} // namespace commonapi
} // namespace v0


// Compatibility
namespace v0_1 = v0;

#endif // V0_COMMONAPI_Park_Distance_Control_STUB_HPP_