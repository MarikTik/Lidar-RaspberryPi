#pragma once

namespace lidar::transmission{
     enum class PacketStatus{
          OK,
          CORRUPTED,
          INCOMPLETE,
     };
}
