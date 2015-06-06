<?php

/**
 * @file article.inc
 * Article nodes migration from drupal 6 to 7.
 */

class ArticleMigration extends SMBNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_bar', 'field_foo');
    $this->addFieldMapping('field_bar:format', 'field_foo:format')
         ->callbacks(array($this, 'mapFormat'));

    $this->addFieldMapping('field_tags', 1)
         ->sourceMigration('Tags');
    $this->addFieldMapping('field_tags:source_type')
         ->defaultValue('tid');


    $this->addFieldMapping('field_tags2', 2)
         ->sourceMigration('Tags2');
    $this->addFieldMapping('field_tags2:source_type')
         ->defaultValue('tid');

    $this->addFieldMapping('field_tags3', 3)
         ->sourceMigration('Tags3');
    $this->addFieldMapping('field_tags3:source_type')
         ->defaultValue('tid');

    $this->addFieldMapping('field_file', 'field_file')
         ->sourceMigration('File');
    $this->addFieldMapping('field_file:file_class')
         ->defaultValue('MigrateFileFid');
  }
}
