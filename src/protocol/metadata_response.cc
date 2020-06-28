/*
 * This file is open source software, licensed to you under the terms
 * of the Apache License, Version 2.0 (the "License").  See the NOTICE file
 * distributed with this work for additional information regarding copyright
 * ownership.  You may not use this file except in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (C) 2019 ScyllaDB Ltd.
 */

#include <kafka4seastar/protocol/metadata_response.hh>

using namespace seastar;

namespace kafka4seastar {

void metadata_response_broker::serialize(std::ostream& os, int16_t api_version) const {
    node_id.serialize(os, api_version);
    host.serialize(os, api_version);
    port.serialize(os, api_version);
    if (api_version >= 1) {
        rack.serialize(os, api_version);
    }
}

void metadata_response_broker::deserialize(std::istream& is, int16_t api_version) {
    node_id.deserialize(is, api_version);
    host.deserialize(is, api_version);
    port.deserialize(is, api_version);
    if (api_version >= 1) {
        rack.deserialize(is, api_version);
    }
}

void metadata_response_partition::serialize(std::ostream& os, int16_t api_version) const {
    error_code.serialize(os, api_version);
    partition_index.serialize(os, api_version);
    leader_id.serialize(os, api_version);
    if (api_version >= 7) {
        leader_epoch.serialize(os, api_version);
    }
    replica_nodes.serialize(os, api_version);
    isr_nodes.serialize(os, api_version);
    if (api_version >= 5) {
        offline_replicas.serialize(os, api_version);
    }
}

void metadata_response_partition::deserialize(std::istream& is, int16_t api_version) {
    error_code.deserialize(is, api_version);
    partition_index.deserialize(is, api_version);
    leader_id.deserialize(is, api_version);
    if (api_version >= 7) {
        leader_epoch.deserialize(is, api_version);
    }
    replica_nodes.deserialize(is, api_version);
    isr_nodes.deserialize(is, api_version);
    if (api_version >= 5) {
        offline_replicas.deserialize(is, api_version);
    }
}

void metadata_response_topic::serialize(std::ostream& os, int16_t api_version) const {
    error_code.serialize(os, api_version);
    name.serialize(os, api_version);
    if (api_version >= 1) {
        is_internal.serialize(os, api_version);
    }
    partitions.serialize(os, api_version);
    if (api_version >= 8) {
        topic_authorized_operations.serialize(os, api_version);
    }
}

void metadata_response_topic::deserialize(std::istream& is, int16_t api_version) {
    error_code.deserialize(is, api_version);
    name.deserialize(is, api_version);
    if (api_version >= 1) {
        is_internal.deserialize(is, api_version);
    }
    partitions.deserialize(is, api_version);
    if (api_version >= 8) {
        topic_authorized_operations.deserialize(is, api_version);
    }
}

void metadata_response::serialize(std::ostream& os, int16_t api_version) const {
    if (api_version >= 3) {
        throttle_time_ms.serialize(os, api_version);
    }
    brokers.serialize(os, api_version);
    if (api_version >= 2) {
        cluster_id.serialize(os, api_version);
    }
    if (api_version >= 1) {
        controller_id.serialize(os, api_version);
    }
    topics.serialize(os, api_version);
    if (api_version >= 8) {
        cluster_authorized_operations.serialize(os, api_version);
    }
}

void metadata_response::deserialize(std::istream& is, int16_t api_version) {
    if (api_version >= 3) {
        throttle_time_ms.deserialize(is, api_version);
    }
    brokers.deserialize(is, api_version);
    if (api_version >= 2) {
        cluster_id.deserialize(is, api_version);
    }
    if (api_version >= 1) {
        controller_id.deserialize(is, api_version);
    }
    topics.deserialize(is, api_version);
    if (api_version >= 8) {
        cluster_authorized_operations.deserialize(is, api_version);
    }
}

}
