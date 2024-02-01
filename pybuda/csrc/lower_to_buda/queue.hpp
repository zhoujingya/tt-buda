// SPDX-FileCopyrightText: © 2024 Tenstorrent AI ULC
//
// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <memory>
#include <optional>

#include "graph_lib/node_types.hpp"
#include "lower_to_buda/common.hpp"
#include "lower_to_buda/device.hpp"
#include "lower_to_buda/op.hpp"

namespace tt {

struct BudaQueueDimensions {
    int grid_r, grid_c;
};

enum BudaQueueLocation { DRAM, HOST };

struct BudaQueueDramLoc {
    std::uint32_t dram_channel;
    std::uint32_t dram_address;
};

struct BudaQueueHostLoc {
    std::uint32_t host_channel;
    std::uint32_t host_address;
};

struct BudaQueue {

    std::string name;
    std::string input_name;
    std::string type;
    std::string memory_access;
    std::string alias;
    int entries;
    int microbatch;
    BudaQueueDimensions dims;
    DataFormat data_format;
    BudaDevice target_device;
    BudaQueueLocation loc;
    std::vector<BudaQueueDramLoc> dram_loc;
    std::vector<BudaQueueHostLoc> host_loc;
    BudaBlocks blocks;
    graphlib::UBlockOrder ublock_order = graphlib::UBlockOrder::R;
    BudaQueueLayout layout = BudaQueueLayout::Tilized;
    TileDim tile_dim_;

    BudaQueue(const std::string &name, const std::string &type, const std::string& memory_access, int device, TileDim tile_dim)
        : name(name), type(type), memory_access(memory_access), target_device(BudaDevice(device)), tile_dim_(tile_dim)  {}

    std::string as_string(int padded_name_length = 0) const;

};

std::ostream &operator<<(std::ostream &os, BudaQueue const &m);
std::ostream &operator<<(std::ostream &os, BudaQueueLocation const &l);
std::ostream &operator<<(std::ostream &os, BudaQueueDramLoc const &l);
std::ostream &operator<<(std::ostream &os, BudaQueueHostLoc const &l);
std::ostream &operator<<(std::ostream &os, BudaQueueLayout const &l);

} // namespace tt

