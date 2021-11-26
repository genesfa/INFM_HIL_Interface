/**
 * Sim To DuT Interface
 *
 * Copyright (C) 2021 Lukas Wagenlehner
 *
 * This file is part of "Sim To DuT Interface".
 *
 * "Sim To DuT Interface" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * "Sim To DuT Interface" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with "Sim To DuT Interface".  If not, see <http://www.gnu.org/licenses/>.
 *
 * @author Lukas Wagenlehner
 * @version 1.0
 */

#ifndef SIM_TO_DUT_INTERFACE_SIMCOMHANDLER_H
#define SIM_TO_DUT_INTERFACE_SIMCOMHANDLER_H

#include <memory>
#include "../Events/SimEvent.h"
#include <string>
#include "../Utility/SharedQueue.h"
#include "../SystemConfig.h"
#include <thread>
#include <chrono>
#include <zmq.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "../SystemConfig.h"
#include <utility>
#include <zmq.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/variant.hpp>

namespace sim_interface {
    class SimComHandler {
    public:
        SimComHandler(std::shared_ptr<SharedQueue<SimEvent>> queueSimToInterface, const SystemConfig& config);

        // async send event to simulation
        void sendEventToSim(const SimEvent &simEvent);

        // run async receive incoming events
        void run();

    private:
        // send an event to the interface
        void sendEventToInterface(const SimEvent &simEvent);

        zmq::socket_t socketSimSub_;
        zmq::socket_t socketSimPub_;
        zmq::context_t context_test;

        // used by sendEventToInterface
        std::shared_ptr<SharedQueue<SimEvent>> queueSimToInterface;
    };
}

#endif //SIM_TO_DUT_INTERFACE_SIMCOMHANDLER_H
