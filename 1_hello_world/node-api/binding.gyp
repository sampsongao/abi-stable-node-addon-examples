{
  "targets": [
    {
      "target_name": "hello",
      "sources": [ "hello.cc" ],
      "include_dirs": [
        "<!(node -p \"require('node-api').include\")"
      ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ]
    }
  ]
}
