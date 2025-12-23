// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/of_fdt.h>
#include <linux/libfdt.h>

static int __init hmbird_dt_fixup(void)
{
	void *fdt = initial_boot_params;
	int soc, hmbird, version_type;

	if (!fdt)
		return 0;

	soc = fdt_path_offset(fdt, "/soc");
	if (soc < 0)
		return 0;

	// Rimuovi oplus,xxbird se esiste
	fdt_del_node(fdt, fdt_subnode_offset(fdt, soc, "oplus,xxbird"));

	// Crea /soc/oplus,hmbird
	hmbird = fdt_add_subnode(fdt, soc, "oplus,hmbird");
	if (hmbird < 0)
		return 0;

	// Crea /soc/oplus,hmbird/version_type
	version_type = fdt_add_subnode(fdt, hmbird, "version_type");
	if (version_type < 0)
		return 0;

	// Imposta type = "HMBIRD_OGKI"
	fdt_setprop_string(fdt, version_type, "type", "HMBIRD_OGKI");

	return 0;
}
early_initcall(hmbird_dt_fixup);
