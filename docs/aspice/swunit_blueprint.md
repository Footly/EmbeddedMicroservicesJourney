# {{ item.label }}
## Description
{{ item.description }}
## Component
- {{ item.component.label }}: {{ item.component.description }}
## Dependencies
{% for dep in item.dependencies -%}
- {{ dep.dependency.label }}: {{ dep.dependency.description }} ({{ dep.visibility }})
{% endfor -%}
## Macros
{%- for macro in item.macros -%}
{%- if macro.label -%}
- {{ macro.label }}: {{ macro.description }} ({{ macro.visibility }}, Configurable: {{ macro.isConfigurable }})
{%- endif %}
{% endfor -%}