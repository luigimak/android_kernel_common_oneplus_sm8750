// SPDX-License-Identifier: GPL-2.0
#include <linux/init.h>
#include <linux/of.h>
#include <linux/slab.h>

static int __init hmbird_add_dt_node(void)
{
	struct device_node *soc, *hmbird, *version_type;
	const char *type_val = "HMBIRD_OGKI";

	// Find /soc
	soc = of_find_node_by_path("/soc");
	if (!soc) {
		pr_err("HMBird: /soc not found\n");
		return -ENODEV;
	}

	// Remove oplus,xxbird if exists
	of_remove_property(soc, of_find_property(soc, "oplus,xxbird", NULL));

	// Create oplus,hmbird
	hmbird = of_new_node(soc, "oplus,hmbird", NULL);
	if (!hmbird) {
		pr_err("HMBird: failed to create hmbird node\n");
		of_node_put(soc);
		return -ENOMEM;
	}

	// Create version_type
	version_type = of_new_node(hmbird, "version_type", NULL);
	if (!version_type) {
		pr_err("HMBird: failed to create version_type\n");
		of_node_put(hmbird);
		of_node_put(soc);
		return -ENOMEM;
	}

	// Set "type"
	of_add_property_string(version_type, "type", type_val);

	pr_info("HMBird: DT node added successfully\n");

	of_node_put(version_type);
	of_node_put(hmbird);
	of_node_put(soc);
	return 0;
}

// Use late_initcall: DT tree is already unflattened
late_initcall(hmbird_add_dt_node);
