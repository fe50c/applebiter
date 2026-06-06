/*
 * ANCS tool
 * Copyright (C) 2026 silibop
 *
 * This file is part of applebiter.
 *
 * Applebiter is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
 * Applebiter is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License along with applebiter. If not, see <https://www.gnu.org/licenses/>. 
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>
#include <plist/plist.h>

#define TOOLNAME "applebiter"

int main() {
	idevice_t device = NULL;
	const char *udid = NULL;
	lockdownd_client_t client = NULL;
	const char *domain = "com.apple.disk_usage";
	const char *key = "TotalDataAvailable";
	plist_t node = NULL;
	
	if(idevice_new(&device, udid) != IDEVICE_E_SUCCESS) {
		printf("device fucked\n");
		return -1;
	}

	lockdownd_error_t err;
	if((err = lockdownd_client_new_with_handshake(device, &client, TOOLNAME)) != LOCKDOWN_E_SUCCESS) {
		printf("lockdownd fucked %s\n", lockdownd_strerror(err));
		return -1;
	}

	if((err = lockdownd_get_value(client, domain, key, &node)) != LOCKDOWN_E_SUCCESS) {
		printf("lockdownd fucked %s\n", lockdownd_strerror(err));
		return -1;
	}
	if(!node) {
		printf("we have no node for some reason?");
	}
	plist_write_to_stream(node, stdout, PLIST_FORMAT_LIMD, 0);
}
