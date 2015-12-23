#ifndef PROGRESSIVEPHOTONMAPSETTINGS_HPP_
#define PROGRESSIVEPHOTONMAPSETTINGS_HPP_

#include "integrators/photon_map/PhotonMapSettings.hpp"

#include "io/JsonObject.hpp"

namespace Tungsten {

struct ProgressivePhotonMapSettings : public PhotonMapSettings
{
    float alpha;
    bool fixedVolumeRadius;
    float volumeGatherRadius;

    ProgressivePhotonMapSettings()
    : alpha(0.3f),
      fixedVolumeRadius(false),
      volumeGatherRadius(gatherRadius)
    {
    }

    void fromJson(const rapidjson::Value &v)
    {
        PhotonMapSettings::fromJson(v);
        JsonUtils::fromJson(v, "alpha", alpha);
        JsonUtils::fromJson(v, "fixed_volume_radius", fixedVolumeRadius);
        if (!JsonUtils::fromJson(v, "volume_gather_radius", volumeGatherRadius))
            volumeGatherRadius = gatherRadius;
    }

    rapidjson::Value toJson(rapidjson::Document::AllocatorType &allocator) const
    {
        rapidjson::Value v = PhotonMapSettings::toJson(allocator);
        v.RemoveMember("type");

        return JsonObject{std::move(v), allocator,
            "type", "progressive_photon_map",
            "alpha", alpha,
            "fixed_volume_radius", fixedVolumeRadius,
            "volume_gather_radius", volumeGatherRadius
        };
    }
};

}

#endif /* PROGRESSIVEPHOTONMAPSETTINGS_HPP_ */
