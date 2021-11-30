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

#ifndef SIM_TO_DUT_INTERFACE_SYSTEMCONFIG_H
#define SIM_TO_DUT_INTERFACE_SYSTEMCONFIG_H

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <fstream>
#include "DuTLogger/DuTLogger.h"

namespace sim_interface {
    /**
     * Class containing the config for the SimComHandler, the SimToDuTInterface and the Logger.
     * All attributes in this class should have default values assigned.
     */
    class SystemConfig {
    public:
        /**
         * Create a new system config with default values.
         */
        SystemConfig() = default;

        // TODO add Logging Config, dont forget to change the serialize methode if you add new attributes

        /**
         * Address of the zmq subscriber.
         */
        std::string socketSimAddressSub = "tcp://localhost:7777";
        /**
         * Address of the zmq publisher.
         */
        std::string socketSimAddressPub = "tcp://*:7778";

        /**
         * Save the config to a File.
         * Does not create a new folder if it dose not exist!
         * @param file File path.
         * @param systemConfig Reference to a system config object.
         */
        static void saveToFile(const std::string &file, SystemConfig &systemConfig) {
            try {
                std::ofstream ofs(file);
                boost::archive::xml_oarchive oa(ofs);
                oa << BOOST_SERIALIZATION_NVP(systemConfig);
                DuTLogger::logMessage("Successfully saved system config to <" + file + ">", LOG_LEVEL::INFO);
            } catch (...) {
                DuTLogger::logMessage("Save system config failed.", LOG_LEVEL::ERROR);
            }
        }

        /**
         * Load the config from a File.
         * @param file File path.
         * @param systemConfig Reference to a system config object.
         * @param createNewIfNotFoundOrInvalid Save the default system config to the file location if the loading is
         * unsuccessful.
         */
        static void
        loadFromFile(const std::string &file, SystemConfig &systemConfig, bool createNewIfNotFoundOrInvalid) {
            try {
                std::ifstream ifs(file);
                boost::archive::xml_iarchive ia(ifs);
                ia >> BOOST_SERIALIZATION_NVP(systemConfig);
            } catch (...) {
                DuTLogger::logMessage("Load system config failed. Fallback to default values.", LOG_LEVEL::ERROR);
                if (createNewIfNotFoundOrInvalid) {
                    sim_interface::SystemConfig::saveToFile(file, systemConfig);
                }
            }
        }

    private:
        friend class boost::serialization::access;

        template<class Archive>
        void serialize(Archive &ar, const unsigned int version) {
            ar & BOOST_SERIALIZATION_NVP(socketSimAddressSub);
            ar & BOOST_SERIALIZATION_NVP(socketSimAddressPub);
            // TODO add all attributes here if they need to be saved and loaded
        }
    };
}

#endif //SIM_TO_DUT_INTERFACE_SYSTEMCONFIG_H
