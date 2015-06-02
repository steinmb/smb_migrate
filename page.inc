<?php

/**
 * @file page.inc
 * Page nodes migration from drupal 6 to 7.
 */

class PageMigration extends SMBNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}
