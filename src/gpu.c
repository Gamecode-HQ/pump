#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <libdrm/drm.h>
#include <libdrm/amdgpu.h>
#include <libdrm/amdgpu_drm.h>

void queryInfo(amdgpu_device_handle device, unsigned info_id, const char *name)
{
    long long result = 0;
    int err = amdgpu_query_info(device, info_id, sizeof(result), &result);
    if (err)
    {
        printf("%s amdgpu_query_info error", name);
        exit(err);
    }

    printf("%s: %lld\n", name, result);
}

void querySensorInfo(amdgpu_device_handle device, unsigned info_id, const char *name)
{
    long long result = 0;
    int err = amdgpu_query_sensor_info(device, info_id, sizeof(result), &result);
    if (err)
    {
        printf("%s amdgpu_query_sensor_info error", name);
        exit(err);
    }

    printf("%s: %lld\n", name, result);
}

int main()
{
    amdgpu_device_handle device = NULL;
    struct amdgpu_bo_alloc_request request = {};
    struct amdgpu_heap_info heapInfo = {};
    int fd = open("/dev/dri/card0", O_RDWR);
    uint32_t version1 = 2;
    uint32_t version2 = 2;
    int err = amdgpu_device_initialize(fd, &version1, &version2, &device);
    if (err)
    {
        puts("amdgpu_device_initialize error");
        return err;
    }

    querySensorInfo(device, AMDGPU_INFO_SENSOR_GFX_SCLK, "AMDGPU_INFO_SENSOR_GFX_SCLK");
    querySensorInfo(device, AMDGPU_INFO_SENSOR_GFX_MCLK, "AMDGPU_INFO_SENSOR_GFX_MCLK");
    querySensorInfo(device, AMDGPU_INFO_SENSOR_GPU_TEMP, "AMDGPU_INFO_SENSOR_GPU_TEMP");
    querySensorInfo(device, AMDGPU_INFO_SENSOR_GPU_LOAD, "AMDGPU_INFO_SENSOR_GPU_LOAD");
    querySensorInfo(device, AMDGPU_INFO_SENSOR_GPU_AVG_POWER, "AMDGPU_INFO_SENSOR_GPU_AVG_POWER");
    querySensorInfo(device, AMDGPU_INFO_SENSOR_VDDGFX, "AMDGPU_INFO_SENSOR_VDDGFX");
    queryInfo(device, AMDGPU_INFO_NUM_BYTES_MOVED, "AMDGPU_INFO_NUM_BYTES_MOVED");
    queryInfo(device, AMDGPU_INFO_VRAM_USAGE, "AMDGPU_INFO_VRAM_USAGE");
    queryInfo(device, AMDGPU_INFO_GTT_USAGE, "AMDGPU_INFO_GTT_USAGE");
    queryInfo(device, AMDGPU_INFO_GDS_CONFIG, "AMDGPU_INFO_GDS_CONFIG");
    queryInfo(device, AMDGPU_INFO_VRAM_GTT, "AMDGPU_INFO_VRAM_GTT");
    queryInfo(device, AMDGPU_INFO_READ_MMR_REG, "AMDGPU_INFO_READ_MMR_REG");
    queryInfo(device, AMDGPU_INFO_DEV_INFO, "AMDGPU_INFO_DEV_INFO");
    queryInfo(device, AMDGPU_INFO_VIS_VRAM_USAGE, "AMDGPU_INFO_VIS_VRAM_USAGE");
    queryInfo(device, AMDGPU_INFO_NUM_EVICTIONS, "AMDGPU_INFO_NUM_EVICTIONS");
    queryInfo(device, AMDGPU_INFO_NUM_VRAM_CPU_PAGE_FAULTS, "AMDGPU_INFO_NUM_VRAM_CPU_PAGE_FAULTS");
    queryInfo(device, AMDGPU_INFO_VRAM_LOST_COUNTER, "AMDGPU_INFO_VRAM_LOST_COUNTER");

    return 0;
}
