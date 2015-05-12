<?php

/**
 * @file article.inc
 * Article nodes migration from drupal 6 to 7.
 */

class ArticleMigration extends SMBNodeMigration {
  public function __construct(array $arguments) {
    parent::__construct($arguments);
  }
}
