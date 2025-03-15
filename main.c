#include <rte_eal.h>
#include <rte_bus_pci.h>
#include <rte_dev.h>
#include <stdio.h>
#include <inttypes.h>

#define PCI_ADDR "0000:b3:00.0"  // 替换为你的设备 PCI 地址
#define BAR_IDX  4               // BAR4 的索引
#define REG_OFFSET 0x2000060     // 寄存器偏移量

int main(int argc, char **argv) {
    // 1. 初始化 EAL 环境（需包含 PCI 白名单）
    const char *eal_args[] = {
        "dpdk_app",
        "-l", "0",               // 指定使用的 CPU 核心
        "--pci-whitelist", PCI_ADDR, // 允许访问目标设备
        "--vfio-intr=legacy",    // VFIO 中断模式
        NULL
    };
    int ret = rte_eal_init(sizeof(eal_args)/sizeof(eal_args[0]) - 1, 
                          (char **)eal_args);
    if (ret < 0) {
        rte_exit(EXIT_FAILURE, "EAL init failed: %d\n", ret);
    }

#if 0
    // 2. 查找 PCI 设备
    struct rte_pci_addr addr;
    if (rte_pci_addr_parse(PCI_ADDR, &addr) != 0) {
        rte_exit(EXIT_FAILURE, "Invalid PCI address\n");
    }

    struct rte_pci_device *pci_dev = NULL;
    FOREACH_DEVICE_ON_PCIBUS(pci_dev) {
        if (rte_pci_addr_cmp(&pci_dev->addr, &addr) == 0) {
            break;
        }
    }

    if (!pci_dev) {
        rte_exit(EXIT_FAILURE, "Device %s not found\n", PCI_ADDR);
    }

    // 3. 检查 BAR4 是否有效
    if (BAR_IDX >= RTE_DIM(pci_dev->mem_resource) || 
        pci_dev->mem_resource[BAR_IDX].addr == NULL) {
        rte_exit(EXIT_FAILURE, "BAR%d not available\n", BAR_IDX);
    }

    // 4. 计算寄存器地址（BAR4 基地址 + 偏移量）
    void *bar4_base = pci_dev->mem_resource[BAR_IDX].addr;
    volatile uint32_t *reg_addr = (volatile uint32_t *)((char *)bar4_base + REG_OFFSET);

    // 5. 读取寄存器值
    uint32_t reg_value = *reg_addr;
    printf("Register value at BAR4 + 0x%x: 0x%08" PRIx32 "\n", REG_OFFSET, reg_value);
#endif
    // 6. 清理 EAL 环境
    rte_eal_cleanup();
    return 0;
}