/*
 * Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __MLX5CTL_IOCTL_H__
#define __MLX5CTL_IOCTL_H__

#include <linux/types.h>

#define MLX5CTL_METHOD_READ     1
#define MLX5CTL_METHOD_WRITE    0
#define MLX5CTL_ENV_VAR_DEBUG   "MLX5CTL_DEBUG"

#define MLX5CTL_DEBUG_PRINT(mf, format, arg...) \
    if (mf->mlx5ctl_env_var_debug) {        \
        printf("%s: %s %d: " format, MLX5CTL_ENV_VAR_DEBUG, __func__, __LINE__, ##arg); \
    }

int mlx5_control_access_register(int fd, void *data_in,
                                 int size_in, __u16 reg_id,
                                 int method, int *reg_status,
                                 mfile* mf);
void mlx5ctl_set_device_id(mfile* mf);

struct mlx5ctl_info {
	__u16 uctx_uid; /* current process allocated UCTX UID */
	__u16 reserved1; /* explicit padding must be zero */
	__u32 uctx_cap; /* current process effective UCTX cap */
	__u32 dev_uctx_cap; /* device's UCTX capabilities */
	__u32 ucap; /* process user capability */
};

struct mlx5ctl_cmdrpc {
	__aligned_u64 in; /* RPC inbox buffer user address */
	__aligned_u64 out; /* RPC outbox buffer user address */
	__u32 inlen; /* inbox buffer length */
	__u32 outlen; /* outbox buffer length */
};

struct mlx5ctl_umem_reg {
	__aligned_u64 addr; /* user address */
	__aligned_u64 len; /* user buffer length */
	__u32 umem_id; /* returned device's umem ID */
	__u32 reserved; /* explicit padding must be zero */
};

struct mlx5ctl_umem_unreg {
	__u32 umem_id;
	__u32 reserved; /* explicit padding must be zero */
};

#define MLX5CTL_MAX_RPC_SIZE (512 * 512) /* max FW RPC buffer size 512 blocks of 512 bytes */

#define MLX5CTL_IOCTL_MAGIC 0x5c

#define MLX5CTL_IOCTL_INFO \
	_IOR(MLX5CTL_IOCTL_MAGIC, 0x0, struct mlx5ctl_info)

#define MLX5CTL_IOCTL_CMDRPC \
	_IOWR(MLX5CTL_IOCTL_MAGIC, 0x1, struct mlx5ctl_cmdrpc)

#define MLX5CTL_IOCTL_UMEM_REG \
	_IOWR(MLX5CTL_IOCTL_MAGIC, 0x2, struct mlx5ctl_umem_reg)

#define MLX5CTL_IOCTL_UMEM_UNREG \
	_IOWR(MLX5CTL_IOCTL_MAGIC, 0x3, struct mlx5ctl_umem_unreg)

#endif /* __MLX5CTL_IOCTL_H__ */
