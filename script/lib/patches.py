#!/usr/bin/env python

import time
import os
import sys

from lib import git


class PatchesList:
  """A list of patches for a specific git repo."""

  @staticmethod
  def from_directory(dir_path, project_root):
    with open(os.path.join(dir_path, '.repo')) as f:
      repo_dir = f.readline().rstrip('\n')
    absolute_repo_path = os.path.join(project_root, repo_dir)
    with open(os.path.join(dir_path, '.patches')) as f:
      patch_filenames = [l.rstrip('\n') for l in f.readlines()]
    assert git.is_repo_root(absolute_repo_path)
    patches = [os.path.join(dir_path, filename)
        for filename in patch_filenames]
    return PatchesList(absolute_repo_path, patches)

  def __init__(self, repo_path, patches):
    self.repo_path = repo_path
    self.patches = patches

  def __len__(self):
    return len(self.patches)

  def import_as_commits(self):
    return git.am(self.repo_path, self.patches)

  def apply(self, commit=False):
    applied = git.apply_patches(self.repo_path, self.patches, index=commit)

    if applied and commit:
      author = 'Electron Build Process <build@electronjs.org>'
      message = 'Apply Electron patches'
      git.commit(self.repo_path, author=author, message=message)

    return applied
