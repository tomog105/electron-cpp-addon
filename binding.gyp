{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "hello.cc" ],
      "include_dirs": [
        "vendor/mruby/include",
        "<!(node -e \"require('nan')\")"
      ],
      'dependencies': [
        'mruby'
      ],
      'link_settings': {
        'libraries': [
          '-lmruby'
        ],
        'library_dirs': [
          '<(PRODUCT_DIR)/../../vendor/mruby/build/host/lib'
        ]
      },
    },
    {
      'target_name': 'mruby',
      'type': 'none',
      'actions': [
        {
          'action_name': 'make_mruby',
          'inputs': [''],
          'outputs': [''],
          "conditions": [
            [ 'OS=="mac"', {
              'variables': {
                # Resolve warnings: object file (..) was built for newer OSX version (10.12) than being linked (10.7)
                'MACOSX_DEPLOYMENT_TARGET': '10.7',
              }
          }]],
          'action': [
            'make', '-C', '<(PRODUCT_DIR)/../../vendor/mruby',
            'MACOSX_DEPLOYMENT_TARGET=<(MACOSX_DEPLOYMENT_TARGET)'
          ],
        }
      ]
    }
  ]
}
