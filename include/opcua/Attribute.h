#pragma once
/*
* ogamma OPC UA C++ SDK
* Copyright(c) One-Way Automation Inc.
* https://onewayautomation.com/opcua-sdk
* All rights reserved.
*/

#include "opcua/RequestHeader.h"
#include "opcua/ResponseHeader.h"
#include "opcua/Enums.h"
#include "opcua/NumericNodeId.h"
#include "opcua/DataValue.h"
#include "opcua/Utils.h"
#include <boost/any.hpp>
#include "opcua/History.h"

namespace OWA {
  namespace OpcUa {
		typedef uint32_t IntegerId;
		typedef std::string NumericRange;
		
		struct ReadValueId {
			ReadValueId() {
				attributeId = 13;
			}
			ReadValueId(const NodeId& nodeId, IntegerId attributeId = 13) {
				this->nodeId = nodeId;
				this->attributeId = attributeId;
			}
			ReadValueId(uint32_t intNodeId, uint16_t namespaceIndex = 0) : nodeId(intNodeId, namespaceIndex) {
				attributeId = 13;
			}
			NodeId				nodeId;
			IntegerId			attributeId;
			NumericRange	indexRange;
			QualifiedName dataEncoding;
		};

    struct ReadRequest {
			ReadRequest() {
				maxAge = 0;
				timestampsToReturn = TimestampsToReturn::Both;
			}
			ReadRequest(const NodeId& nodeId):ReadRequest() {
				nodesToRead.push_back(nodeId);
			}
			virtual ~ReadRequest() {
			}

      static RequestResponseTypeId getTypeId() {
        return RequestResponseTypeId::ReadRequest;
      }
      RequestHeader				header;
			Duration						maxAge;
			TimestampsToReturn	timestampsToReturn;
			std::vector<ReadValueId>	nodesToRead;
			
			boost::any					context;

			typedef std::shared_ptr<ReadRequest> Ptr;
    };

    struct ReadResponse {
      ResponseHeader header;
			std::vector<DataValue> results;
			std::vector<DiagnosticInfo> diagnosticInfos;
			inline bool isGood() { return Utils::isGood(*this);}
			typedef std::shared_ptr<ReadResponse> Ptr;
			~ReadResponse() {
			}
    };

		struct WriteValue
		{
			WriteValue() { attributeId = 13; /*Value attribute */}
			WriteValue(const NodeId& nodeId, const DataValue& dataValue);
			NodeId nodeId;
			IntegerId attributeId;
			std::string indexRange;
			DataValue value;
		};

    struct WriteRequest {
      static RequestResponseTypeId getTypeId() {
        return RequestResponseTypeId::WriteRequest;
      }
			WriteRequest();
			WriteRequest(const WriteValue& writeValue);
      RequestHeader header;
			boost::any		context;
			std::vector<WriteValue> nodesToWrite;

			typedef std::shared_ptr<WriteRequest> Ptr;
    };

    struct WriteResponse {
      ResponseHeader header;
			std::vector<StatusCode> results;
			std::vector<DiagnosticInfo> diagnosticInfos;
			inline bool isGood() { return Utils::isGood(*this); }
    };

		struct HistoryReadValueId
	{
		HistoryReadValueId();
		HistoryReadValueId(const NodeId& nodeId);
		NodeId				nodeId;
		NumericRange	indexRange;
		QualifiedName	dataEncoding;
		ByteString		continuationPoint;
	};
    struct HistoryReadRequest{
			HistoryReadRequest();
			
      static RequestResponseTypeId getTypeId() {
        return RequestResponseTypeId::HistoryReadRequest;
      }
      RequestHeader header;
			boost::any		context;
			ExtensionObject::Ptr historyReadDetails;
			TimestampsToReturn timestampsToReturn;
			bool releaseContinuationPoints;
			std::vector<HistoryReadValueId> nodesToRead;

			typedef std::shared_ptr <HistoryReadRequest> Ptr;
    };

		struct HistoryReadResult
		{
			HistoryReadResult();

			StatusCode statusCode;
			ByteString continuationPoint;
			ExtensionObject::Ptr historyData;
		};
		
		struct HistoryReadResponse {
      ResponseHeader header;
			std::vector<HistoryReadResult> results;
			std::vector<DiagnosticInfo> diagnosticInfos;
			inline bool isGood() { return Utils::isGood(*this); }
			typedef std::shared_ptr<HistoryReadResponse> Ptr;
    };

    struct HistoryUpdateRequest {
      static RequestResponseTypeId getTypeId() {
        return RequestResponseTypeId::HistoryUpdateRequest;
      }
      RequestHeader header;
			boost::any		context;

			std::vector<ExtensionObject::Ptr>	historyUpdateDetails;

			typedef std::shared_ptr<HistoryUpdateRequest> Ptr;

    };
    struct HistoryUpdateResponse {
      ResponseHeader header;
			inline bool isGood() { return Utils::isGood(*this); }

			std::vector<HistoryUpdateResult>	results;
			std::vector<DiagnosticInfo>				diagnosticInfos;

			typedef std::shared_ptr<HistoryUpdateResponse> Ptr;
    };

  }
}