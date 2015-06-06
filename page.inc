<?php

/**
 * @file page.inc
 * Page nodes migration from drupal 6 to 7.
 */

class PageMigration extends SMBNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->addFieldMapping('field_entityref_taxonomy', 3)
         ->sourceMigration('Tags3');
  }
}
