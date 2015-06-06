<?php

class SMBFile6Migration extends DrupalFile6Migration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('preserve_files', NULL, FALSE)
         ->defaultValue(FALSE);
    $this->addFieldMapping('file_replace', NULL, FALSE)
         ->defaultValue(FILE_EXISTS_REPLACE);
  }
}
