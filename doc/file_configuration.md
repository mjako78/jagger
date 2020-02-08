# JAGGER CONFIGURATION VIA INI FILE

It is possible to configure Jagger via **jagger.ini** configuration file.  
This is a simple ini file, with no section, only key-value pairs.

The available keys are as follows:

- rootLogger=&lt;TRACE|DEBUG|INFO|WARNING|ERROR|FATAL&gt;
- appender.type=&lt;FILE|CONSOLE&gt;

where type can be any combination of **FILE** and **CONSOLE**.

In a future release I'm plannig to include a threshold property, defined as follows:

- appender.&lt;type&gt;.threshold=&lt;TRACE|DEBUG|INFO|WARNING|ERROR|FATAL&gt;

Currently *threshold* is not used.

## Console appender scenario

No others properties are needed.

## File appender scenario

In a **FILE** appender scenario, others properties need to be specified:

- appender.file.filename=&lt;path_of_logfile.log&gt;

There are also additional properties, not required:

- appender.file.append=&lt;TRUE|FALSE&gt;
- appender.file.layout=&lt;DAILY|SIZE&gt;
- appender.file.maxSize=&lt;MAX_FILE_SIZE_MB&gt;
- appender.file.maxFiles=&lt;MAX_FILES_TO_KEEP&gt;

Currently *maxFiles* property is not used.