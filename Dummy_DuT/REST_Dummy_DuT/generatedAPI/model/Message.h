/**
 * HIL - REST Dummy DuT
 * This is a sample component description for a REST server as dummy DuT
 *
 * The version of the OpenAPI document: 1.0.0
 * 
 *
 * NOTE: This class is auto generated by OpenAPI-Generator 5.2.1.
 * https://openapi-generator.tech
 * Do not edit the class manually.
 */


#ifndef Message_H_
#define Message_H_


#include <string>
#include <memory>
#include <boost/property_tree/ptree.hpp>

namespace dummy_dut::rest::model {

/// <summary>
/// 
/// </summary>
    class Message {
    public:
        Message();

        virtual ~Message();

        std::string toJsonString(bool prettyJson = false);

        void fromJsonString(std::string const &jsonString);

        boost::property_tree::ptree toPropertyTree();

        void fromPropertyTree(boost::property_tree::ptree const &pt);

        /////////////////////////////////////////////
        /// Message members

        /// <summary>
        ///
        /// </summary>
        std::string getKey() const;

        void setKey(std::string value);

        /// <summary>
        ///
        /// </summary>
        std::string getStatus() const;

        void setStatus(std::string value);

    protected:
        std::string m_Key;
        std::string m_Status;
    };

}

#endif /* Message_H_ */
