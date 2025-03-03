/*
 * Copyright(c) 2021 Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*!
 * @file bf_dpdk_port_if.h
 *
 *
 * Details DPDK Port-level structures and APIs
 */

#ifndef BF_DPDK_PORT_IF_H_INCLUDED
#define BF_DPDK_PORT_IF_H_INCLUDED

/* Allow the use in C++ code.  */
#ifdef __cplusplus
extern "C" {
#endif

#include <bf_types/bf_types.h>
//#include <bf_pal/bf_pal_types.h>

/**
 * Identifies if a port-directions
 */
typedef enum bf_pm_port_dir_e {
	PM_PORT_DIR_DEFAULT = 0,  // both rx and tx
	PM_PORT_DIR_TX_ONLY = 1,
	PM_PORT_DIR_RX_ONLY = 2,
	PM_PORT_DIR_MAX
} bf_pm_port_dir_e;

/*
 * TODO: These values should be defined in
 * P4 DPDK Interface File
 */
#define PORT_NAME_LEN 64
#define PORT_TYPE_LEN 16
#define PORT_DIR_LEN 16
#define PCIE_BDF_LEN 16
#define PIPE_NAME_LEN 64
#define MEMPOOL_NAME_LEN 64
#define PCAP_FILE_NAME_LEN 128
#define DEV_ARGS_LEN 256
#define DIR_REG_ARRAY_SIZE 256
#define QEMU_ARGS_LEN 64
#define SOCK_IP_LEN 64
#define SOCK_PATH_LEN 256
#define MAC_STR_LEN 18

#define PORT_IN_BURST_SIZE 32
#define PORT_OUT_BURST_SIZE 1
#define PORT_MTU_MAX 65535

/**
 * DPDK Port Types
 */
enum dpdk_port_type_t {
	BF_DPDK_TAP,    /*!< DPDK Tap Port */
	BF_DPDK_LINK,   /*!< DPDK Link Port */
	BF_DPDK_SOURCE,   /*!< DPDK Source Port */
	BF_DPDK_SINK,   /*!< DPDK Sink Port */
	BF_DPDK_RING,   /*!< DPDK Ring Port */
	BF_DPDK_PORT_MAX,   /*!< DPDK Invalid Port */
};

/**
 * DPDK Tap Port Attributes
 */
struct tap_port_attributes_t {
	uint32_t mtu;           /*!< Port MTU */
};

/**
 * DPDK Link Port Attributes
 */
struct link_port_attributes_t {
	char pcie_domain_bdf[PCIE_BDF_LEN]; /*!< PCIE Domain BDF */
	char dev_args[DEV_ARGS_LEN]; /*!< Device Arguments */
	uint32_t dev_hotplug_enabled; /*!< Device Hotplug Enabled Flag */
};

/**
 * DPDK Source Port Attributes
 */
struct source_port_attributes_t {
	char file_name[PCAP_FILE_NAME_LEN]; /*!< PCAP File Name */
};

/**
 * DPDK Sink Port Attributes
 */
struct sink_port_attributes_t {
	char file_name[PCAP_FILE_NAME_LEN]; /*!< PCAP File Name */
};

/**
 * DPDK Ring Port Attributes
 */
struct ring_port_attributes_t {
	uint32_t size; /*!< Size of the ring port */
};

/**
 * DPDK Port Attributes
 */
struct port_attributes_t {
	char port_name[PORT_NAME_LEN];         /*!< Port Name */
	char mempool_name[MEMPOOL_NAME_LEN];   /*!< Mempool Name */
	char pipe_in[PIPE_NAME_LEN];           /*!< Pipeline Name in Input
						*   Direction*/
	char pipe_out[PIPE_NAME_LEN];          /*!< Pipeline Name in Output
						*   Direction*/
	bf_pm_port_dir_e port_dir;              /*!< Port Direction */
	uint32_t port_in_id;    /*!< Port ID for Pipeline in Input Direction */
	uint32_t port_out_id;   /*!< Port ID for Pipeline in Output Direction */
	uint8_t net_port;    /*!< if set port is network port else host port*/
	enum dpdk_port_type_t port_type;            /*!< Port Type */

	union {
		struct tap_port_attributes_t tap;       /*!< Tap Port Attributes */
		struct link_port_attributes_t link;     /*!< Link Port Attributes */
		struct source_port_attributes_t source; /*!< Source Port Attributes */
		struct sink_port_attributes_t sink;     /*!< Sink Port Attributes */
		struct ring_port_attributes_t ring;     /*!< Ring Port Attributes */
	};
};

/**
 * DPDK Hotplug attributes
 */
struct hotplug_attributes_t {
	uint32_t qemu_socket_port;
	char qemu_vm_mac_address[MAC_STR_LEN];
	char qemu_socket_ip[SOCK_IP_LEN];
	char qemu_vm_netdev_id[QEMU_ARGS_LEN];
	char qemu_vm_chardev_id[QEMU_ARGS_LEN];
	char qemu_vm_device_id[QEMU_ARGS_LEN];
	char native_socket_path[SOCK_PATH_LEN];
	bool qemu_hotplug;
};

/**
 * Port Mgr Key Field IDs
 */
enum port_mgr_key_field_ids {
        DEV_PORT_ID = 0,
};

/**
 * Port Mgr Data Field IDs
 */
enum port_mgr_data_field_ids {
        PORT_NAME_ID = 0,
        PORT_TYPE_ID,
        PORT_DIR_ID,
        MTU_ID,
        PIPE_IN_ID,
        PIPE_OUT_ID,
        PORT_IN_ID,
        PORT_OUT_ID,
        MEMPOOL_ID,
        PCIE_BDF_ID,
        FILE_NAME_ID,
        DEV_ARGS_ID,
        DEV_HOTPLUG_ENABLED_ID,
        SIZE_ID,
        NET_PORT_ID,
};

/**
 * Port Mgr Key Fields
 */
struct port_mgr_key_fields {
        uint32_t dev_port;
};

/**
 * Port Mgr Data Fields
 */
struct port_mgr_data_fields {
	uint32_t mtu;
	uint32_t port_in_id;
	uint32_t port_out_id;
	uint32_t dev_hotplug_enabled;
	uint32_t size;
	uint8_t net_port;
	char port_name[PORT_NAME_LEN];
	char port_type[PORT_TYPE_LEN];
	char port_dir[PORT_DIR_LEN];
	char pipe_in[PIPE_NAME_LEN];
	char pipe_out[PIPE_NAME_LEN];
	char mempool_name[MEMPOOL_NAME_LEN];
	char pcie_domain_bdf[PCIE_BDF_LEN];
	char file_name[PCAP_FILE_NAME_LEN];
	char dev_args[DEV_ARGS_LEN];
};

#ifdef __cplusplus
}
#endif /* C++ */
#endif  // BF_DPDK_PORT_IF_H_INCLUDED
