{% set header_guard = item.label.upper() + "_H" %}
#ifndef {{ header_guard }}
#define {{ header_guard }}

// 1. Header includes
{% for include in item.dependencies -%}
{% if include.visibility == "public" -%}
#include "{{ include.dependency.label }}.h"
{% endif -%}
{% endfor %}

// 2. Macros
{%- for macro in item.macros -%}
{% if macro.visibility == "public" %}
/**
 * @id {{ macro.id }}
 * @brief {{ macro.description }}
 */
{% if macro.isConfigurable -%}
#ifndef {{macro.label}}
#define {{ macro.label }} {{ macro.implementation }}
#endif // {{macro.label}}
{% else -%}
#define {{ macro.label }} {{ macro.implementation }}
{% endif -%}
{% endif %}
{%- endfor %}

// 3. Typedefs declarations
{%- for typedef in item.typedefs -%}
{% if typedef.visibility == "public" %}
/**
 * @id {{ typedef.id }}
 * @brief {{ typedef.description }}
 */
typedef {{ typedef.type.label }} {{ typedef.label }};
{% endif %}
{%- endfor %}

// 4. Structures and Unions forward declarations
{% for struct in item.structures -%}
{% if struct.visibility == "public" -%}
/**
 * @id {{ struct.id }}
 * @brief {{ struct.description }}
 */
{% if struct.type == "struct" -%}
typedef struct {{ struct.label }} {{ struct.label }};
{% elif struct.type == "union" %}
typedef union {{ struct.label }} {{ struct.label }};
{% endif %}
{% endif %}
{%- endfor %}

// 5. Enums typedefs declarations
{%- for en in item.enums -%}
{% if en.visibility == "public" %}
/**
 * @id {{ en.id }}
 * @brief {{ en.description }}
 */
typedef enum {
    {% for en_mem in en.enumerators -%}
    {% if en_mem.value -%}
    {{ en_mem.label }} = {{ en_mem.value }}, /!**< @id {{ en_mem.id }} @brief {{ en_mem.description }} */
    {% else -%}
    {{ en_mem.label }}, /!**< @id {{ en_mem.id }} @brief {{ en_mem.description }} */
    {%- endif -%}
    {% endfor %}
} {{ en.label }};
{% endif %}
{%- endfor %}

// 6. Callback typedefs declarations
{%- for callback in item.callbacks -%}
{% if callback.visibility == "public" %}
/**
 * @id {{ callback.id }}
 * @brief {{ callback.description }}
{%- for param in callback.parameters %}
 * @param {{ param.label }}: {{ param.datatype.label }}{% if param.description %} - {{ param.description }}{% endif %}
{%- endfor %}
 * @return {{ callback.returntype.datatype.label }}
 */
typedef {{ callback.returntype.datatype.label }} (*{{ callback.label }})( 
    {%- for param in callback.parameters -%}
    {{ param.datatype.label }} {{ param.qualifiers }} {{ param.label }}{%- for arr in param.array -%}[{{ arr }}]{%- endfor -%}{% if not loop.last %}, {% endif %}
    {%- endfor -%}
);
{% endif %}
{% endfor %}

// 7. Structures and Unions definitions
{%- for struct in item.structures -%}
{%- if struct.visibility == "public" %}
{%- if struct.type == "struct" %}
struct {{ struct.label }} {
{% elif struct.visibility == "union" %}
union {{ struct.label }} {
{%- endif -%}
    {%- for member in struct.members %}
    {{ member.type.label }} {{ member.label }}{%- for arr in member.array -%}[{{ arr }}]{%- endfor -%}; /!**< @id {{ member.id }} @brief {{ member.description }} */
    {%- endfor %}
};
{% endif %}
{%- endfor %}

// 8. Functions declarations
{%- for func in item.functions -%}
{% if func.visibility == "public" %}
/**
 * @id {{ func.id }}
 * @brief {{ func.description }}
{%- for param in func.parameters %}
 * @param {{ param.label }}: {{ param.datatype.label }}{% if param.description %} - {{ param.description }}{% endif %}
{%- endfor %}
 * @return {{ func.returntype.datatype.label }}
 */
{{ func.returntype.datatype.label }} {{ func.label }}(
    {%- for param in func.parameters -%}
    {{ param.datatype.label }} {{ param.qualifiers }} {{ param.label }}{%- for arr in param.array -%}[{{ arr }}]{%- endfor -%}{% if not loop.last %}, {% endif %}
    {%- endfor -%}
);
{% endif %}
{%- endfor %}

#endif  // {{ header_guard }}